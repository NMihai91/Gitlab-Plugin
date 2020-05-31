#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setDesign();
    center();

    currentUser = new User();

    connect(bntLogin, SIGNAL (released()), this, SLOT (on_bntLogin_clicked()));
}

void LoginWindow::setDesign(){
    setFixedSize(700, 500);
    setWindowTitle("GitlabPlugin - Login page");

    //Set a centralWidget for mainPage
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //set LoginWidget
    loginWidget = new QWidget(centralWidget);
    loginWidget->setGeometry(QRect(250, 100, 201, 311));

    //Set Grid where I put username/password
    gridLayoutWidget = new QWidget(loginWidget);
    gridLayoutWidget->setGeometry(QRect(0, 70, 201, 141));

    gridLayoutLogin = new QGridLayout(gridLayoutWidget);
    gridLayoutLogin->setContentsMargins(4, 0, 0, 0);

    //Put this to Grid - it's a block with lblPassword and textEditPassword
    horizontalLayoutPassword = new QHBoxLayout();
    lblPassword = new QLabel(gridLayoutWidget);
    lblPassword->setText("password: ");

    //add lblPassword tot horizontalLayoutPassword
    horizontalLayoutPassword->addWidget(lblPassword);

    lineEditPassword = new QLineEdit(gridLayoutWidget);
    //Hide the password entered
    lineEditPassword->setEchoMode(QLineEdit::Password);

    //Add lineEditPassword to horizontalLayoutPassword
    horizontalLayoutPassword->addWidget(lineEditPassword);

    //add horizontalLayoutPassword to gridLayoutLogin - add to position  1
    gridLayoutLogin->addLayout(horizontalLayoutPassword, 1, 0, 1, 1);

    //Put this to Grid - it's a block with lblPassword and textEditPassword
    horizontalLayoutUsername = new QHBoxLayout();
    lblUsername = new QLabel(gridLayoutWidget);
    lblUsername->setText("username: ");

    //add lblUsername tot horizontalLayoutUsername
    horizontalLayoutUsername->addWidget(lblUsername);

    lineEditUsername = new QLineEdit(gridLayoutWidget);
    //Add lineEditUsername to horizontalLayoutUsername
    horizontalLayoutUsername->addWidget(lineEditUsername);

    //add to position 0
    gridLayoutLogin->addLayout(horizontalLayoutUsername, 0, 0, 1, 1);

    //Add topLogin Widget for Logo
    topLoginWidget = new QWidget(loginWidget);
    topLoginWidget->setGeometry(QRect(0, 0, 201, 71));

    //Define a Label logo
    lblLogo = new QLabel(topLoginWidget);
    lblLogo->setGeometry(QRect(100, 20, 61, 41));
    QFont font;
    font.setPointSize(17);
    lblLogo->setFont(font);
    lblLogo->setText("Login");

    //Define a Widget for btnLogin
    bottomWidgetBtn = new QWidget(loginWidget);
    bottomWidgetBtn->setGeometry(QRect(0, 210, 201, 51));

    bntLogin = new QPushButton(bottomWidgetBtn);
    bntLogin->setGeometry(QRect(120, 10, 81, 31));
    QFont font1;
    font1.setPointSize(10);
    bntLogin->setFont(font1);
    bntLogin->setText("Login");


    //add errorWidget
    errorWidget = new QWidget(loginWidget);
    errorWidget->setGeometry(QRect(0, 260, 201, 51));

    verticalLayoutWidget = new QWidget(errorWidget);
    verticalLayoutWidget->setGeometry(QRect(0, 0, 201, 51));

    //add vertical layout for error
    verticalLayoutError = new QVBoxLayout(verticalLayoutWidget);
    verticalLayoutError->setContentsMargins(0, 0, 0, 0);

    //add errorLbl
    lblError = new QLabel(verticalLayoutWidget);

    //add lblError to verticalLayoutError
    verticalLayoutError->addWidget(lblError);
}

void LoginWindow::on_bntLogin_clicked()
{
    LoginWindow::currentUser->setUsername(lineEditUsername->text().toStdString());
    LoginWindow::currentUser->setPassword(lineEditPassword->text().toStdString());

    login();
}

QString LoginWindow::accessToken;
QString LoginWindow::currentUserName;

void LoginWindow::login()
{
    SimpleMenu *menu = new SimpleMenu();
    accessToken = QString::fromStdString(LoginWindow::currentUser->generateToken());
    currentUserName = QString::fromStdString(LoginWindow::currentUser->getUsername());
    
    if(accessToken == "Username or password is incorrect!")
    {
        loginMessageError.setText("Username or password is incorrect!");
        lblError->setText("Incorrect username or password!");
    }else{
        if(menu->isVisible())
        {
            menu->hide();
            this->show();
        }
        else
        {
            this->hide();
            menu->show();
        }
    }
}

void LoginWindow::center(){
    // geometry of the main window
    QRect qr = this->frameGeometry();

    // center point of screen
    QScreen *qc = QGuiApplication::primaryScreen();
    QPoint cp = qc->geometry().center();

    // move rectangle's center point to screen's center point
    qr.moveCenter(cp);

    // top left of rectangle becomes top left of window centering it
    this->move(qr.topLeft());
}

LoginWindow::~LoginWindow()
{
}

