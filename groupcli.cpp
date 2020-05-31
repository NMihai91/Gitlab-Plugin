#include "groupcli.h"

GroupCLI::GroupCLI()
{
}

Group group;

QString GroupCLI::createGroup(QString &name, QString &description, QString &visibility){
    group.setName(name.toStdString());
    group.setDescription(description.toStdString());
    group.setVisibility(visibility.toStdString());

    return QString::fromStdString(group.createGroup(LoginWindow::accessToken.toStdString()));
}

QList<QString> GroupCLI::groupList(){
    QList<QString> tempGroupList;

    group.groupList(LoginWindow::accessToken.toStdString());

    for(auto &name: group.groupName){
        QString qstr = QString::fromStdString(name);

        tempGroupList.push_back(qstr);
    }

    return tempGroupList;
}

void GroupCLI::deleteGroup(int delItem){
    group.setChoiceDelete(delItem);

    group.deleteGroup(LoginWindow::accessToken.toStdString());
}
