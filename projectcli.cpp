#include "projectcli.h"

ProjectCLI::ProjectCLI()
{

}

Project project;
QVector<QString> ProjectCLI::tempProjectId;

QList<QString> ProjectCLI::projectList(){
    tempProjectId.clear();

    QList<QString> tempProjectList;

    project.projectList(LoginWindow::accessToken.toStdString(), LoginWindow::currentUserName.toStdString());

    for(auto name: project.projectName){
        QString qstr = QString::fromStdString(name);

        tempProjectList.push_back(qstr);
    }

    for(auto &id: project.getProjectId()){
        tempProjectId.push_back(QString::fromStdString(id));
    }

    return tempProjectList;
}

