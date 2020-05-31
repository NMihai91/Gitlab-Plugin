/*
 * User.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#include "User.h"

User::User() {
	// TODO Auto-generated constructor stub
}

//Mask the password
int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

//Mask the password
std::string getpass(const char *prompt, bool show_asterisk = true)
{
  const char BACKSPACE=127;
  const char RETURN=10;

  std::string password;
  unsigned char ch=0;

  std::cout << prompt;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 std::cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;

             if(show_asterisk)
                 std::cout << '*';
         }
    }
  std::cout << std::endl;

  return password;
}

void User::signIn(){
	std::string password;

	std::cout << "Username/e-mail: ";
	std::cin >> this->username;
	std::cin.ignore(256, '\n');

	password = getpass("Password: ", true);
	setPassword(password);
}

std::string User::generateToken(){
	Utils utils;
	CURL *gitPlugin = curl_easy_init();

	std::string info = "{\"grant_type\": \"password\",  \"username\" : \"" + getUsername() + "\", \"password\" : \"" + getPassword() + "\"}";

	//std::cout << info << std::endl; //print info
	struct curl_slist *header = nullptr;
	header = curl_slist_append(header, "Content-Type: application/json");
	curl_easy_setopt(gitPlugin, CURLOPT_URL, "https://gitlab.com/oauth/token");
	curl_easy_setopt(gitPlugin, CURLOPT_NOPROGRESS, 1L);

	curl_easy_setopt(gitPlugin, CURLOPT_POSTFIELDS, info.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(gitPlugin, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(gitPlugin, CURLOPT_TCP_KEEPALIVE, 1L);

	//Extract token from Json
	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	const std::string accessToken(jsonData["access_token"].asString());
	
	if(!accessToken.empty()){
		return accessToken;
	}

	return "Username or password is incorrect!";
}

void User::setUsername(std::string username){
	this->username = username;
}

void User::setPassword(std::string password){
	this->password = password;
}

std::string User::getUsername() const{
	return this->username;
}

std::string User::getPassword() const{
	return this->password;
}

std::string User::getAccesToken() const{
	return this->accesToken;
}

User::~User() {
	// TODO Auto-generated destructor stub
}

User::User(const User &other) {
	// TODO Auto-generated constructor stub

}
