#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void sendMessage();

private:
    QTextEdit *chatDisplay;
    QLineEdit *messageInput;
    QPushButton *sendButton;
};

#endif // MAINWINDOW_H
