#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QDesktopWidget>
#include <QScreen>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <QComboBox>
#include <QListWidget>

#include "groupcli.h"
#include "projectcli.h"
#include "branchcli.h"

class SimpleMenu : public QMainWindow {
	Q_OBJECT

 public:
    SimpleMenu(QWidget *parent = nullptr);
    ~SimpleMenu();

	void design();
  	void center();
 public slots:
    void create_group();
    void delete_group();
    void list_groups();
    void setGroupInfo();
    void pressDelGroup();

    void create_branch();
    void infoCreateBranch();
    void list_branches();
    void infoDeleteBranch();
    void selBranchToDelete(QListWidgetItem *item);
    void delete_branch();
    void infoBranches(QListWidgetItem *item);
    void selProjectBranchToDelete(QListWidgetItem *item);

    void list_projects();
 private:
    int selectedBranchToDelete, selectedProjectBranchToDelete;
    QPushButton *btnCreateGroup;
    QWidget *centralwidget, *widgetListGroup, *widgetListProjects, *widgetList;
    QLineEdit *lineEditName, *lineEditDescription, *lineEditNameBranch;
    QLabel *lblIsCreateGroup, *labelMessageDelete, *lblErrorCreateBranch, *labelProjecList, *labelBranchList;
    QComboBox *comboBoxVisibility;
    QListWidget *listViewGroups, *listViewProjects, *listViewBranches;
};
