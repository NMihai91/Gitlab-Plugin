#ifndef GROUPCLI_H
#define GROUPCLI_H

#include <QString>
#include <QList>
#include "Group.h"
#include "loginwindow.h"

class GroupCLI
{
public:
    GroupCLI();

    QList<QString> groupList();
    QString createGroup(QString &name, QString &description, QString &visibility);
    void deleteGroup(int delItem);
};

#endif // GROUPCLI_H
