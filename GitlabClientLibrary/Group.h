/*
 * Group.h
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#ifndef SRC_GROUP_H_
#define SRC_GROUP_H_

#include "Utils.h"

#include <exception>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sstream>
#include "curl/curl.h"
#include <json-c/json.h>
#include <json/json.h>
#include <termios.h>

#include <vector>
#include <algorithm>

class Group {
public:
	Group();
	virtual ~Group();
	Group(const Group &other);

	std::string getName() const;
	std::string getDescription() const;
	std::string getPath() const;
	std::string getVisibility() const;
    void setChoiceDelete(int tempDel);
    //Use it for interface/QT to show the groups
    std::vector<std::string> groupName;
    void setName(std::string name);
    void setDescription(std::string description);
    void setVisibility(std::string visibility);
    void setPath();

	//Check if the information is valid
	bool isDataOk();
	//Create new Group
	std::string createGroup(const std::string &accessToken);
	//Show Group List
    std::vector<std::string> groupList(const std::string &accessToken);
	//Delete a Group
	void deleteGroup(const std::string &accessToken);
private:
	std::string name, path, visibility, description;
	std::vector<std::string> groupId;
    int tempChoiceDelete;
};

#endif /* SRC_GROUP_H_ */
