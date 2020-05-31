#ifndef PROJECTCLI_H
#define PROJECTCLI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "Project.h"
#include "loginwindow.h"

class ProjectCLI
{
public:
    ProjectCLI();

    QList<QString> projectList();
    static QVector<QString> tempProjectId;
    void setProjectId();
};

#endif // PROJECTCLI_H
