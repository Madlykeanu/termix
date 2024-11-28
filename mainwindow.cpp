#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create central widget and layouts
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *inputLayout = new QHBoxLayout();
    
    // Create chat display
    chatDisplay = new QTextEdit(this);
    chatDisplay->setReadOnly(true);
    chatDisplay->setPlaceholderText("Messages will appear here...");
    
    // Create input field and send button
    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Type your message here...");
    sendButton = new QPushButton("Send", this);
    
    // Add widgets to input layout
    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);
    
    // Add widgets to main layout
    mainLayout->addWidget(chatDisplay);
    mainLayout->addLayout(inputLayout);
    
    // Set central widget
    setCentralWidget(centralWidget);
    
    // Connect signals and slots
    connect(sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(messageInput, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);
    
    // Set window properties
    setWindowTitle("Chat Interface");
    resize(400, 500);
}

void MainWindow::sendMessage()
{
    QString message = messageInput->text().trimmed();
    if (!message.isEmpty()) {
        chatDisplay->append("You: " + message);
        messageInput->clear();
    }
    messageInput->setFocus();
}
