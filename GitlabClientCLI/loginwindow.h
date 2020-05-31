#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QtDebug>
#include <QMessageBox>
#include <QStyle>
#include <QDesktopWidget>
#include <QScreen>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

#include "menu.h"
#include "Utils.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void setDesign();
    void center();
    Utils utils;

    static QString accessToken;
    static QString currentUserName;
private:
    User *currentUser;
    QString  username, password;
    QMessageBox loginMessageError;
    QWidget *centralwidget, *loginWidget, *gridLayoutWidget, *topLoginWidget, *bottomWidgetBtn, *errorWidget, *verticalLayoutWidget;
    QGridLayout *gridLayoutLogin;
    QHBoxLayout *horizontalLayoutPassword, *horizontalLayoutUsername;
    QLabel *lblPassword, *lblUsername, *lblLogo, *lblError;
    QLineEdit *lineEditPassword, *lineEditUsername;
    QPushButton *bntLogin;
    QVBoxLayout *verticalLayoutError;

private slots:
    void login();
    void on_bntLogin_clicked();
};
#endif // LOGINWINDOW_H
