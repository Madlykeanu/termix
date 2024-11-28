#pragma once

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <memory>
#include "../api/api_client.h"

namespace termix {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void handleUserInput();
    void handleApiResponse(const QString& response);
    void configureApiKey();

private:
    void setupUi();
    void setupConnections();
    void appendToChat(const QString& text, bool isUser = false);
    void executeCommand(const QString& command);

    QTextEdit* chatDisplay;
    QLineEdit* inputField;
    QPushButton* sendButton;
    QPushButton* configButton;

    std::unique_ptr<api::ApiClient> apiClient;
};

} // namespace termix
