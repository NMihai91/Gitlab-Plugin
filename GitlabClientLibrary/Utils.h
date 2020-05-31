/*
 * Utils.h
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "User.h"
#include "Group.h"
#include "Branch.h"
#include "Project.h"

//#include <iostream>
//#include <string.h>
//#include <unistd.h>
// #include <sstream>
// #include "curl/curl.h"
// #include <json-c/json.h>
// #include <json/json.h>
// #include <termios.h>

class Utils {
public:
	Utils();
	virtual ~Utils();
	Utils(const Utils &other);

	void setAccessToken(std::string accessToken);
	std::string getAccessToken() const;
	
	//Login menu
	void login() const;
	void loginMenu();
	//Operations menu
	void subMenu() const;
	void operationsMenu();
	//Funtions of data parsing
	Json::Value jsonData(CURL* gitPlugin);
	static Json::Value stringToJson(const std::string &tempChunkMemory);

private:
    std::string accessToken;
};

#endif /* SRC_UTILS_H_ */
