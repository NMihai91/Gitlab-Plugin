/*
 * Project.h
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#ifndef SRC_PROJECT_H_
#define SRC_PROJECT_H_

#include <iostream>
#include "Utils.h"
#include <vector>

class Project {
public:
	Project();
	virtual ~Project();
	Project(const Project &other);

	void setName(std::string &name);
	std::string getName() const;
	//Set project info from keyboard
	void setData();
    std::vector<std::string> projectName;
	std::string createProject(const std::string &accesToken);
    std::vector<std::string> projectList(const std::string &accessToken, const std::string &username);
    std::vector<std::string> membershipProjectList(const std::string &accessToken, const std::string &username); 
    void getProject(const std::string &accessToken, const std::string &username, int tempChoiceProject);
    std::string deleteProject(const std::string &accessToken, const std::string &username, int tempChoiceDelete);
    std::vector<std::string> getProjectId() const;
private:
	std::string name;
    std::vector<std::string> projectId;
};

#endif /* SRC_PROJECT_H_ */
