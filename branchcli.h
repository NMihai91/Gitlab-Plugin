#ifndef BRANCHCLI_H
#define BRANCHCLI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "Branch.h"
#include "loginwindow.h"
#include "projectcli.h"

class BranchCLI
{
public:
    BranchCLI();

    QList<QString> listBranch(int tempProjectPositionData);
    int createBranch(int positionProjectIdInVector, QString &tempName);   
    void deleteBranch(int tempPositionDeletedBranch, int tempPositionProjectDelBranch);
};

#endif // BRANCHCLI_H
