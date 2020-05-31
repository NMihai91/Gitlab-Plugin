#include "menu.h"
#include "loginwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QCoreApplication>
#include <QTextStream>
#include <QSignalMapper>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>

SimpleMenu::SimpleMenu(QWidget *parent)
    : QMainWindow(parent) { 

    SimpleMenu::center();
    SimpleMenu::design();
}

GroupCLI groupCLI;
ProjectCLI projectCLI;
BranchCLI branchCLI;

void SimpleMenu::design(){
  setFixedSize(700, 500);
  setWindowTitle(QApplication::translate("menu", "GitlabPlugin - Menu page"));

  QWidget *centralwidget = new QWidget(this);
  setCentralWidget(centralwidget);

  QLabel *label = new QLabel(centralwidget);
  label->setGeometry(QRect(160, 160, 421, 131));
  label->setText("GitlabPlugin - demo project");
  QFont font;
  font.setPointSize(21);
  label->setFont(font);

  QAction *createGroup= new QAction("&Create group",this); //actions
  QAction *deleteGroup= new QAction("&Delete group",this);
  QAction *listGroups= new QAction("&List groups",this);
  QAction *createProject= new QAction("&Create project",this);
  QAction *listProjectsAll= new QAction("&List projects where you have access",this);
  QAction *listProjectsOwned= new QAction("&List projects I owned",this);
  QAction *getProject= new QAction("&Get details about one project",this);
  QAction *deleteProject= new QAction("&Delete project",this);
  QAction *listBranches= new QAction("&List branches",this);
  QAction *createBranch= new QAction("&Create branches",this);
  QAction *deleteBranch= new QAction("&Delete branch",this);
 
  QMenu *groups;
  groups = menuBar()->addMenu("&Management Groups"); //add menu
  groups->addAction(createGroup); //add group menu
  groups->addAction(deleteGroup);
  groups->addAction(listGroups);
  
  QMenu *projects;
  projects = menuBar()->addMenu("&Management Projects");
  projects->addAction(createProject);
  projects->addAction(listProjectsAll);
  projects->addAction(listProjectsOwned);
  projects->addAction(getProject);
  projects->addAction(deleteProject);
  
  QMenu *branches;
  branches = menuBar()->addMenu("&Management Branches");
  branches->addAction(createBranch);
  branches->addAction(listBranches);
  branches->addAction(deleteBranch);
  
  QAction *quit=menuBar()->addAction("Quit Application");
  connect(quit, &QAction::triggered, qApp, &QApplication::quit);

  connect(createGroup,&QAction::triggered,this, &SimpleMenu::create_group);
  connect(deleteGroup,&QAction::triggered,this, &SimpleMenu::delete_group);
  connect(listGroups,&QAction::triggered,this, &SimpleMenu::list_groups);
  
  connect(listProjectsOwned,&QAction::triggered,this, &SimpleMenu::list_projects);

  connect(createBranch,&QAction::triggered,this, &SimpleMenu::create_branch);
  connect(listBranches,&QAction::triggered,this, &SimpleMenu::list_branches);
  connect(deleteBranch,&QAction::triggered,this, &SimpleMenu::infoDeleteBranch);
}

void SimpleMenu::create_group(){
    //all page - centralWidget
    QWidget *centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    setWindowTitle("Create Group");

    QWidget *widgetCreateGroup = new QWidget(centralwidget);
    widgetCreateGroup->setGeometry(QRect(220, 70, 231, 341));

    QWidget *widgetLogoCG = new QWidget(widgetCreateGroup);
    widgetLogoCG->setGeometry(QRect(0, 0, 231, 91));

    QLabel *lblCreateGroup = new QLabel(widgetLogoCG);
    lblCreateGroup->setGeometry(QRect(70, 20, 121, 31));
    QFont font;
    font.setPointSize(13);
    font.setBold(false);
    font.setWeight(50);
    lblCreateGroup->setFont(font);
    lblCreateGroup->setText("Create Group");

    QWidget *widgetCGBody = new QWidget(widgetCreateGroup);
    widgetCGBody->setGeometry(QRect(0, 90, 231, 151));

    QWidget *verticalLayoutWidget = new QWidget(widgetCGBody);
    verticalLayoutWidget->setGeometry(QRect(0, 0, 231, 151));

    QVBoxLayout *verticalLayoutCGBody = new QVBoxLayout(verticalLayoutWidget);
    verticalLayoutCGBody->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *horizontalLayoutName = new QHBoxLayout();
    QLabel *lblName = new QLabel(verticalLayoutWidget);
    QFont font1;
    font1.setPointSize(10);
    lblName->setFont(font1);
    lblName->setText("Name:           ");
    horizontalLayoutName->addWidget(lblName);

    lineEditName = new QLineEdit(verticalLayoutWidget);
    horizontalLayoutName->addWidget(lineEditName);

    verticalLayoutCGBody->addLayout(horizontalLayoutName);

    QHBoxLayout *horizontalLayoutDescription = new QHBoxLayout();
    QLabel *lblDescription = new QLabel(verticalLayoutWidget);
    lblDescription->setFont(font1);
    lblDescription->setText("Description:    ");
    horizontalLayoutDescription->addWidget(lblDescription);

    lineEditDescription = new QLineEdit(verticalLayoutWidget);
    horizontalLayoutDescription->addWidget(lineEditDescription);

    verticalLayoutCGBody->addLayout(horizontalLayoutDescription);

    QHBoxLayout *horizontalLayoutVisibility = new QHBoxLayout();
    QLabel *lblVisibility = new QLabel(verticalLayoutWidget);
    lblVisibility->setFont(font1);
    lblVisibility->setText("Visibility: ");
    horizontalLayoutVisibility->addWidget(lblVisibility);

    comboBoxVisibility = new QComboBox(verticalLayoutWidget);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(comboBoxVisibility->sizePolicy().hasHeightForWidth());
    comboBoxVisibility->setSizePolicy(sizePolicy);
    comboBoxVisibility->addItem("private");
    comboBoxVisibility->addItem("public");

    horizontalLayoutVisibility->addWidget(comboBoxVisibility);
    verticalLayoutCGBody->addLayout(horizontalLayoutVisibility);

    QWidget *widget = new QWidget(widgetCreateGroup);
    widget->setGeometry(QRect(-1, 240, 231, 51));

    btnCreateGroup = new QPushButton(widget);
    btnCreateGroup->setGeometry(QRect(134, 12, 91, 31));
    btnCreateGroup->setFont(font1);
    btnCreateGroup->setText("Create Group");

    lblIsCreateGroup = new QLabel(widgetCreateGroup);
    lblIsCreateGroup->setGeometry(QRect(0, 290, 231, 51));

    connect(btnCreateGroup, SIGNAL (released()), this, SLOT (setGroupInfo()));
}

void SimpleMenu::setGroupInfo(){
    QString qstr;

    QString tempName = lineEditName->text();
    QString tempDescription = lineEditDescription->text();
    QString tempVisibility = comboBoxVisibility->currentText();
    qstr = groupCLI.createGroup(tempName, tempDescription, tempVisibility);

    if(qstr.toStdString() == "The group was created!"){
        lblIsCreateGroup->setText("The group was created!");
    }else{
        lblIsCreateGroup->setText("The group could not be created!");
    }
}

void SimpleMenu::delete_group(){
    list_groups();

    widgetListGroup->setGeometry(QRect(230, 70, 271, 321));
    widgetList->setGeometry(QRect(0, 70, 271, 201));
    listViewGroups->setGeometry(QRect(0, 0, 271, 201));
    setWindowTitle("Delete Group");

    QPushButton *pushButton = new QPushButton(widgetListGroup);
    pushButton->setGeometry(QRect(190, 290, 81, 31));
    QFont font1;
    font1.setPointSize(10);
    pushButton->setFont(font1);
    pushButton->setText("Delete");

    QWidget *verticalLayoutWidget = new QWidget(widgetListGroup);
    verticalLayoutWidget->setGeometry(QRect(-1, 329, 271, 51));

    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    labelMessageDelete = new QLabel(verticalLayoutWidget);

    connect(pushButton, SIGNAL (released()), this, SLOT (pressDelGroup()));
}

void SimpleMenu::pressDelGroup(){
   int selectedRow = -1;

   try {
       selectedRow = listViewGroups->currentRow();

       if(selectedRow == -1){
           throw QString("Please select an item!");
       }
       groupCLI.deleteGroup(selectedRow);

       delete_group();
   } catch (QString &ex) {
       labelMessageDelete->setText(ex);
   }
}

void SimpleMenu::list_groups(){
    //all page - centralWidget
    QWidget *centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    setWindowTitle("Group list");

    widgetListGroup = new QWidget(centralwidget);
    widgetListGroup->setGeometry(QRect(230, 70, 271, 321));

    QWidget *widgetLogo = new QWidget(widgetListGroup);
    widgetLogo->setGeometry(QRect(0, 0, 271, 71));

    QLabel *labelTopLogoGroup = new QLabel(widgetLogo);
    labelTopLogoGroup->setGeometry(QRect(90, 30, 121, 31));
    labelTopLogoGroup->setText("Group list");
    QFont font;
    font.setPointSize(12);
    labelTopLogoGroup->setFont(font);

    widgetList = new QWidget(widgetListGroup);
    widgetList->setGeometry(QRect(0, 70, 271, 251));
    listViewGroups = new QListWidget(widgetList);
    listViewGroups->setGeometry(QRect(0, 0, 271, 251));

    //populate the list
    QList<QString> tempListGroups;
    tempListGroups = groupCLI.groupList();
    listViewGroups->addItems(tempListGroups);
}

void SimpleMenu::list_projects(){
    //all page - centralWidget
    QWidget *centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    setWindowTitle("Project List");

    widgetListProjects = new QWidget(centralwidget);
    widgetListProjects->setGeometry(QRect(110, 40, 471, 401));

    labelProjecList = new QLabel(widgetListProjects);
    labelProjecList->setGeometry(QRect(200, 10, 111, 31));
    labelProjecList->setText("Project List");
    QFont font;
    font.setPointSize(12);
    labelProjecList->setFont(font);

    listViewProjects = new QListWidget(widgetListProjects);
    listViewProjects->setGeometry(QRect(110, 60, 271, 201));

    //populate the list
    QList<QString> tempListProjects;
    tempListProjects = projectCLI.projectList();
    listViewProjects->addItems(tempListProjects);
}

void SimpleMenu::create_branch(){
    list_projects();

    setWindowTitle("Create Branch");
    QLabel *lblLogoCreateBranch = new QLabel(widgetListProjects);
    lblLogoCreateBranch->setGeometry(QRect(190, 290, 121, 31));
    lblLogoCreateBranch->setText("Create Branch");
    QFont font;
    font.setPointSize(12);
    lblLogoCreateBranch->setFont(font);

    QLabel *lblNameBranch = new QLabel(widgetListProjects);
    lblNameBranch->setGeometry(QRect(120, 330, 51, 21));
    lblNameBranch->setText("Name:");
    QFont font1;
    font1.setPointSize(10);
    lblNameBranch->setFont(font1);

    lineEditNameBranch = new QLineEdit(widgetListProjects);
    lineEditNameBranch->setGeometry(QRect(170, 330, 141, 21));

    QPushButton *btnCreateBranch = new QPushButton(widgetListProjects);
    btnCreateBranch->setGeometry(QRect(320, 330, 61, 23));
    btnCreateBranch->setText("Create");

    QWidget *verticalLayoutWidget = new QWidget(widgetListProjects);
    verticalLayoutWidget->setGeometry(QRect(0, 360, 471, 41));

    QVBoxLayout *verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    lblErrorCreateBranch = new QLabel(verticalLayoutWidget);
    verticalLayout->addWidget(lblErrorCreateBranch);

    connect(btnCreateBranch, SIGNAL (released()), this, SLOT (infoCreateBranch()));
}

void SimpleMenu::infoCreateBranch(){
    int idSelectedProject;
    int choice = -1;
    QString branchName;

    try {
        choice = listViewProjects->currentRow();

        if(choice == -1 || lineEditNameBranch->text().isEmpty()){
            throw QString("Please select an item or fill the data!");
        }

        branchName = lineEditNameBranch->text();
        idSelectedProject = listViewProjects->currentRow();

        if(branchCLI.createBranch(idSelectedProject, branchName)){
            lblErrorCreateBranch->setText("The Branch couldn't be created!");
        }else{
            lblErrorCreateBranch->setText("The Branch was created!");
        }

    } catch (QString &ex) {
        labelMessageDelete->setText(ex);
    }
}

void SimpleMenu::list_branches(){
    list_projects();

    listViewProjects->setGeometry(QRect(110, 40, 271, 151));

    labelBranchList = new QLabel(widgetListProjects);
    labelBranchList->setGeometry(QRect(200, 220, 101, 31));
    labelBranchList->setText("Branch List");
    QFont font;
    font.setPointSize(12);
    labelBranchList->setFont(font);
    listViewBranches = new QListWidget(widgetListProjects);
    listViewBranches->setGeometry(QRect(110, 250, 271, 151));

    connect(listViewProjects, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(infoBranches(QListWidgetItem *)));
}

void SimpleMenu::infoBranches(QListWidgetItem *item){
    if (!item){
        return;
    }

    //populate the list
    QList<QString> tempListBranches = branchCLI.listBranch(listViewProjects->row(item));
    listViewBranches->clear();
    listViewBranches->addItems(tempListBranches);
}

void SimpleMenu::infoDeleteBranch(){
    list_branches();

    setWindowTitle("Delete Branch");
    labelProjecList->setGeometry(QRect(150, 10, 111, 31));
    listViewProjects->setGeometry(QRect(60, 40, 271, 151));
    labelBranchList->setGeometry(QRect(150, 220, 111, 31));
    listViewBranches->setGeometry(QRect(60, 250, 271, 151));

    QPushButton *pushButton = new QPushButton(widgetListProjects);
    pushButton->setGeometry(QRect(360, 280, 75, 91));
    pushButton->setText("Delete");

    //keep the selected branch position
    connect(listViewBranches, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(selBranchToDelete(QListWidgetItem *)));

    //keep the selected project position
    connect(listViewProjects, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(selProjectBranchToDelete(QListWidgetItem *)));

    connect(pushButton, SIGNAL (released()), this, SLOT (delete_branch()));
}

void SimpleMenu::selBranchToDelete(QListWidgetItem *item){
    if (!item){
        return;
    }

    selectedBranchToDelete = listViewBranches->row(item);
}

void SimpleMenu::selProjectBranchToDelete(QListWidgetItem *item){
    if (!item){
        return;
    }

    selectedProjectBranchToDelete = listViewProjects->row(item);
}

void SimpleMenu::delete_branch(){
    branchCLI.deleteBranch(selectedBranchToDelete, selectedProjectBranchToDelete);

    infoDeleteBranch();
}

void SimpleMenu::center(){
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

SimpleMenu::~SimpleMenu()
{
}
