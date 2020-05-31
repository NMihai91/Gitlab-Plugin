#include "branchcli.h"

BranchCLI::BranchCLI()
{

}

Branch branch;

int BranchCLI::createBranch(int projectPositionId, QString &tempName){   
    QString tempVectorId = ProjectCLI::tempProjectId[projectPositionId];
    std::string tempProjectId = tempVectorId.toStdString();

    branch.setName(tempName.toStdString());

    return branch.newBranch(LoginWindow::accessToken.toStdString(), tempProjectId);
}

QList<QString> BranchCLI::listBranch(int tempProjectPositionData){
    QList<QString> tempBranchList;

    QString tempVectorId = ProjectCLI::tempProjectId[tempProjectPositionData];
    std::string tempProjectId = tempVectorId.toStdString();

    branch.branchList(LoginWindow::accessToken.toStdString(), tempProjectId);

    for(auto &name: branch.branchName){
        QString qstr = QString::fromStdString(name);

        tempBranchList.push_back(qstr);
    }

    return tempBranchList;
}

void BranchCLI::deleteBranch(int tempPositionDelBranch, int tempPositionProjectDelBranch){
    QString tempVectorProjectId = ProjectCLI::tempProjectId[tempPositionProjectDelBranch];
    std::string tempProjectId = tempVectorProjectId.toStdString();

    branch.deleteBranch(LoginWindow::accessToken.toStdString(), tempProjectId, tempPositionDelBranch);
}
