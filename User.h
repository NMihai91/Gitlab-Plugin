/*
 * User.h
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#ifndef SRC_USER_H_
#define SRC_USER_H_

#include "Utils.h"
#include <json/json.h>
#include "curl/curl.h"

//#include <iostream>
//#include <cstdlib>
//#include <string.h>
//#include <unistd.h>
//#include <sstream>
//#include <json-c/json.h>
//#include <termios.h>

class User {
public:
	User();
	virtual ~User();
	User(const User &other);

	void setUsername(std::string username);
	void setPassword(std::string password);
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getAccesToken() const;
	//Set user & password
	void signIn();
	//Generate Token
	std::string generateToken();
private:
	std::string username, password, accesToken;
};

#endif /* SRC_USER_H_ */
