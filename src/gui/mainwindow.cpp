#include "mainwindow.h"
#include "../utils/config.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>
#include <spdlog/spdlog.h>

namespace termix {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , apiClient(api::ApiClient::create("openai"))
{
    setupUi();
    setupConnections();
}

void MainWindow::setupUi() {
    auto centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto mainLayout = new QVBoxLayout(centralWidget);

    // Chat display
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    mainLayout->addWidget(chatDisplay);

    // Input area
    auto inputLayout = new QHBoxLayout();
    
    inputField = new QLineEdit(this);
    inputLayout->addWidget(inputField);

    sendButton = new QPushButton("Send", this);
    inputLayout->addWidget(sendButton);

    configButton = new QPushButton("Configure API Key", this);
    inputLayout->addWidget(configButton);

    mainLayout->addLayout(inputLayout);

    // Set window properties
    resize(800, 600);
    setWindowTitle("Termix - Natural Language Terminal Interface");
}

void MainWindow::setupConnections() {
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::handleUserInput);
    connect(inputField, &QLineEdit::returnPressed, this, &MainWindow::handleUserInput);
    connect(configButton, &QPushButton::clicked, this, &MainWindow::configureApiKey);
}

void MainWindow::handleUserInput() {
    QString input = inputField->text().trimmed();
    if (input.isEmpty()) return;

    // Clear input field
    inputField->clear();

    // Display user input
    appendToChat(input, true);

    // Check if it's a command
    if (input.startsWith("/")) {
        executeCommand(input);
        return;
    }

    // Get API key
    std::string apiKey = utils::Config::getInstance().getApiKey("openai");
    if (apiKey.empty()) {
        QMessageBox::warning(this, "API Key Missing",
            "Please configure your OpenAI API key first.");
        return;
    }

    // Make API request
    apiClient->chatCompletion(
        input.toStdString(),
        apiKey,
        [this](const std::string& response, bool success) {
            // Use Qt::QueuedConnection to ensure we update UI from main thread
            QMetaObject::invokeMethod(this, "handleApiResponse",
                Qt::QueuedConnection,
                Q_ARG(QString, QString::fromStdString(response)));
        }
    );
}

void MainWindow::handleApiResponse(const QString& response) {
    appendToChat(response);
}

void MainWindow::configureApiKey() {
    bool ok;
    QString apiKey = QInputDialog::getText(this, "Configure API Key",
        "Enter your OpenAI API key:", QLineEdit::Normal,
        QString::fromStdString(utils::Config::getInstance().getApiKey("openai")),
        &ok);

    if (ok && !apiKey.isEmpty()) {
        utils::Config::getInstance().setApiKey("openai", apiKey.toStdString());
        utils::Config::getInstance().saveToFile("config.json");
    }
}

void MainWindow::appendToChat(const QString& text, bool isUser) {
    QString formattedText = QString("%1 %2\n")
        .arg(isUser ? "You:" : "Assistant:")
        .arg(text);
    chatDisplay->append(formattedText);
}

void MainWindow::executeCommand(const QString& command) {
    // Handle special commands
    if (command == "/clear") {
        chatDisplay->clear();
        return;
    }

    // Execute system command (you might want to add security checks here)
    QProcess process;
    process.start("cmd.exe", QStringList() << "/c" << command.mid(1));
    process.waitForFinished();

    QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
    QString error = QString::fromLocal8Bit(process.readAllStandardError());

    if (!output.isEmpty()) {
        appendToChat("Command output:\n" + output);
    }
    if (!error.isEmpty()) {
        appendToChat("Command error:\n" + error);
    }
}

} // namespace termix
