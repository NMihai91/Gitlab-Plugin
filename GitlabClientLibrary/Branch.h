/*
 * Branch.h
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#ifndef SRC_BRANCH_H_
#define SRC_BRANCH_H_

#include "Project.h"

class Branch{
public:
	Branch();
	virtual ~Branch();
	Branch(const Branch &other);

    int newBranch(const std::string &accessToken, std::string &tempProjectId);
    std::vector<std::string> branchList(const std::string &accessToken, std::string &tempProjectId);
    void deleteBranch(const std::string &accessToken, std::string &tempProjectId, int tempChoiceBranch);

    void setName(std::string name);
	std::string getName() const;
    std::vector<std::string> branchName;
private:
	std::string name, projectSelectedId;
};

#endif /* SRC_BRANCH_H_ */
