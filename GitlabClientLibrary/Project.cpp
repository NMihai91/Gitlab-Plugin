/*
 * Project.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#include "Project.h"

Project::Project() {
	// TODO Auto-generated constructor stub

}

void Project::setData(){
	std::cin.ignore(256, '\n');
	std::cout << "Project name: ";
	std::getline(std::cin, this->name);
}

std::string Project::createProject(const std::string &accessToken){
	Utils utils;
	CURL *gitPlugin = curl_easy_init();

	std::string info = "{\"name\" : \"" + getName() + "\"}";

	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());


	curl_easy_setopt(gitPlugin, CURLOPT_URL, "https://gitlab.com/api/v4/projects?default_branch");
	curl_easy_setopt(gitPlugin, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(gitPlugin, CURLOPT_POSTFIELDS, info.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);

	//Verify if the project was created/ if id == nullptr then the group couldn't be create
	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	const std::string id(jsonData["id"].asString());

	if(!id.empty()){
		return "The project was created!";
	}

	//return the message
	const std::string message(jsonData["message"].asString());

	return message;
}

void Project::membershipProjectList(const std::string &accessToken,const std::string &username){
	Utils utils;
	CURL *gitPlugin = curl_easy_init();
	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	std::string url = "https://gitlab.com/api/v4/users/";
	url.append(username);
	url.append("/projects?membership");
	curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPGET, 1L);

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	//Show projects
	for (auto it = jsonData.begin(); it != jsonData.end(); ++it)
	{
		std::cout << it.key() << ": ";
		std::cout << (*it)["name"].asString() << "\n";
	}
}

std::vector<std::string> Project::projectList(const std::string &accessToken,const std::string &username){
	this->projectId.clear();
    this->projectName.clear();

	Utils utils;
	CURL *gitPlugin = curl_easy_init();
	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	std::string url = "https://gitlab.com/api/v4/users/";
	url.append(username);
	url.append("/projects?owned");
	curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPGET, 1L);

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	for (auto it = jsonData.begin(); it != jsonData.end(); ++it)
	{
		this->projectId.push_back((*it)["id"].asString());
        this->projectName.push_back((*it)["name"].asString());
	}

    return this->projectName;
}

void Project::getProject(const std::string &accessToken,const std::string &username, int tempChoiceproject){
	projectList(accessToken, username);

	Utils utils;
	CURL *gitPlugin = curl_easy_init();
	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	std::string url = "https://gitlab.com/api/v4/projects/";
    url.append(this->projectId[tempChoiceproject]);
	curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPGET, 1L);

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	std::cout << std::endl << "Info about the selected Group:" << std::endl;
	std::cout << "Name: " << jsonData["name"].asString() << std::endl;
	std::cout << "Description: " << jsonData["description"].asString() << std::endl;
	std::cout << "Visibility: " << jsonData["visibility"].asString() << std::endl;
	std::cout << "Path: " << jsonData["path"].asString() << std::endl;
	std::cout << "Created at: " << jsonData["created_at"].asString() << std::endl;
	std::cout << "Default branch: " << jsonData["default_branch"].asString() << std::endl;
	std::cout << "Readme url: " << jsonData["readme_url"].asString() << std::endl;
	std::cout << "Web url: " << jsonData["web_url"].asString() << std::endl;
	std::cout << "Http_url to Repository: " << jsonData["http_url_to_repo"].asString() << std::endl;
	std::cout << "Is empty repo: " << jsonData["empty_repo"].asString() << std::endl;
	//std::cout << "Owner: " << jsonData["owner.username"].asString() << std::endl;
}

void Project::deleteProject(const std::string &accessToken,const std::string &username, int tempChoiceDelete){
	Utils utils;
	projectList(accessToken,username);

	CURL* gitPlugin = curl_easy_init();
  	CURLcode res = CURLE_OK;

	if(gitPlugin) {
		struct curl_slist *header = nullptr;
		std::string tempToken = "Authorization: Bearer ";
		tempToken.append(accessToken);
		header = curl_slist_append(header, "Content-Type: application/json");
		header = curl_slist_append(header, tempToken.c_str());
	
		std::string url = "https://gitlab.com/api/v4/projects/";
		
		url.append(this->projectId[tempChoiceDelete]);
		/* This is just the server URL */ 
		curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	
		curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);

		/* Set the DELETE command specifying the existing folder */ 
		curl_easy_setopt(gitPlugin, CURLOPT_CUSTOMREQUEST, "DELETE");

		res = curl_easy_perform(gitPlugin);		
 		if(res != CURLE_OK){
      		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}	
	
		curl_easy_cleanup(gitPlugin);
	}
}

std::vector<std::string> Project::getProjectId() const{
	return this->projectId;
}

void Project::setName(std::string &name){
	this->name = name;
}

std::string Project::getName() const{
	return this->name;
}

Project::~Project() {
	// TODO Auto-generated destructor stub
}

Project::Project(const Project &other) {
	// TODO Auto-generated constructor stub

}

