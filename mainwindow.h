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
#include <QScrollBar>
#include <QFont>
#include <QPalette>
#include <QGraphicsDropShadowEffect>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void sendMessage();
    void adjustScrollBar();

private:
    void setupStyles();
    
    QTextEdit *chatDisplay;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QWidget *inputContainer;
};

#endif // MAINWINDOW_H
