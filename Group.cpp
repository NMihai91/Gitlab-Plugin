/*
 * Group.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#include "Group.h"

Group::Group() {
	// TODO Auto-generated constructor stub

}

bool Group::isDataOk(){
	std::cin.ignore(256, '\n');
	std::cout << "Group name: ";
	std::getline(std::cin, this->name);

	std::cout << "Group description: ";
	std::getline(std::cin, this->description);

	std::cout << "Set visibility(1 private/ 2 internal/ 3 public): ";
	int tempChoiceVis;
	std::string tempVis;

	//I must modify this request
	try{
		std::cin >> tempChoiceVis;

		if(tempChoiceVis != 1 && tempChoiceVis != 2 && tempChoiceVis != 3){
			throw std::string ("Incorrect visibility!");
		}

		if(tempChoiceVis == 1 ){
			this->visibility = "private";
		}

		if(tempChoiceVis == 2 ){
			this->visibility = "internal";
		}

		if(tempChoiceVis == 3 ){
			this->visibility = "public";
		}

	}catch(std::string& e){
		std::cout << e << std::endl;
		return false;
	}



    return true;
}

void Group::setPath(){

    this->path = this->name;
    for (long unsigned i = 0; i < this->path.size(); ++i) {
        if (this->path[i] == ' ') {

            this->path[i] = '-';
        }
    }

    this->path.append("GitlabPlugin");
}

std::string Group::createGroup(const std::string &accessToken){
	Utils utils;
    setPath();
	CURL *gitPlugin = curl_easy_init();

	std::string info = "{\"name\" : \"" + getName() + "\", \"path\" : \"" + getPath() + "\", \"description\" : \"" + getDescription() + "\", \"visibility\" : \"" + getVisibility() + "\"}";

	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());


	curl_easy_setopt(gitPlugin, CURLOPT_URL, "https://gitlab.com/api/v4/groups");
	curl_easy_setopt(gitPlugin, CURLOPT_NOPROGRESS, 1L);

	curl_easy_setopt(gitPlugin, CURLOPT_POSTFIELDS, info.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);

	//Verify if the group was created/ if id == nullptr then the group couldn't be create
	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);
	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	const std::string id(jsonData["id"].asString());

	if(!id.empty()){
		return "The group was created!";
	}

	//return the message
	const std::string message(jsonData["message"].asString());

	return message;
}

std::vector<std::string> Group::groupList(const std::string &accessToken){
	//Of every time empty Id_vector
	this->groupId.clear();
    this->groupName.clear();

	Utils utils;
	CURL *gitPlugin = curl_easy_init();

	struct curl_slist *header = nullptr;

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());

	curl_easy_setopt(gitPlugin, CURLOPT_URL, "https://gitlab.com/api/v4/groups");
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPGET, 1L);
	//curl_easy_setopt(gitPlugin, CURLOPT_CUSTOMREQUEST, "GET");

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);
	
	for (auto it = jsonData.begin(); it != jsonData.end(); ++it)
	{
		//Add the position in vector
		this->groupId.push_back((*it)["id"].asString());
        this->groupName.push_back((*it)["name"].asString());
	}

    return this->groupName;
}

std::string Group::deleteGroup(const std::string &accessToken){
	CURL* gitPlugin = curl_easy_init();
  	CURLcode res = CURLE_OK;

	if(gitPlugin) {
		struct curl_slist *header = nullptr;
		std::string tempToken = "Authorization: Bearer ";
		tempToken.append(accessToken);
		header = curl_slist_append(header, "Content-Type: application/json");
		header = curl_slist_append(header, tempToken.c_str());
	
		std::string url = "https://gitlab.com/api/v4/groups/";
		url.append(this->groupId[tempChoiceDelete]);
		/* This is just the server URL */ 
		curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	
		curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);

		/* Set the DELETE command specifying the existing folder */ 
		curl_easy_setopt(gitPlugin, CURLOPT_CUSTOMREQUEST, "DELETE");

		res = curl_easy_perform(gitPlugin);	
		curl_easy_cleanup(gitPlugin);		
 		if(res != CURLE_OK){
      		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			curl_easy_strerror(res);
			return "The group was not deleted!";
		}	
	}
	return "The group was deleted!";
}

std::string Group::getDescription() const{
	return this->description;
}

std::string Group::getName() const{
	return name;
}

std::string Group::getPath() const{
	return path;
}

std::string Group::getVisibility() const{
	return visibility;
}

void Group::setName(std::string name){
    this->name = name;
}
void Group::setDescription(std::string description){
    this->description = description;
}
void Group::setVisibility(std::string visibility){
    this->visibility = visibility;
}

void Group::setChoiceDelete(int tempDel){
    this->tempChoiceDelete = tempDel;
}

Group::~Group() {
	// TODO Auto-generated destructor stub
}

Group::Group(const Group &other) {
	// TODO Auto-generated constructor stub

}
