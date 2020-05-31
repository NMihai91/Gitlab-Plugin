/*
 * Branch.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#include "Branch.h"

Branch::Branch() {
	// TODO Auto-generated constructor stub
}

int Branch::newBranch(const std::string &accessToken, std::string &tempProjectId){

	struct curl_slist *header = nullptr;

	Utils utils;
	CURL *gitPlugin = curl_easy_init();

	////////////////////////////////////////REF is master - we should change it//////////////////////////////////////
	std::string info = "{\"branch\" : \"" + getName() + "\", \"ref\" : \"master\"}";

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	std::string url = "https://gitlab.com/api/v4/projects/";
    url.append(tempProjectId);
	url.append("/repository/branches");

	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());


	curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_NOPROGRESS, 1L);

	curl_easy_setopt(gitPlugin, CURLOPT_POSTFIELDS, info.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	if(jsonData["can_push"].asString() == "true")
	{
		return 0;
	}

	return 1;
}

std::vector<std::string> Branch::branchList(const std::string &accessToken, std::string &tempProjectId){
	//Clear BranchId_vector
	this->branchName.clear();

	struct curl_slist *header = nullptr;

	Utils utils;
    CURL *gitPlugin = curl_easy_init();

	std::string tempToken = "Authorization: Bearer ";
	tempToken.append(accessToken);

	std::string url = "https://gitlab.com/api/v4/projects/";
    url.append(tempProjectId);
	url.append("/repository/branches");
	
	curl_easy_setopt(gitPlugin, CURLOPT_URL, url.c_str());
	header = curl_slist_append(header, "Content-Type: application/json");
	header = curl_slist_append(header, tempToken.c_str());
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(gitPlugin, CURLOPT_HTTPGET, 1L);

	Json::Value jsonData;
	jsonData = utils.jsonData(gitPlugin);

	for (auto it = jsonData.begin(); it != jsonData.end(); ++it)
	{
		//Add the position in vector
		this->branchName.push_back((*it)["name"].asString());
	}

    return this->branchName;
}

void Branch::deleteBranch(const std::string &accessToken, std::string &tempProjectId, int tempChoiceBranch){
	Utils utils;
	CURL *gitPlugin = curl_easy_init();
	CURLcode res = CURLE_OK;

    branchList(accessToken, tempProjectId);

	if(gitPlugin){
		struct curl_slist *header = nullptr;
		std::string tempToken = "Authorization: Bearer ";

		tempToken.append(accessToken);
		header = curl_slist_append(header, "Content-Type: application/json");
		header = curl_slist_append(header, tempToken.c_str());

		std::string url = "https://gitlab.com/api/v4/projects/";
        url.append(tempProjectId);
		url.append("/repository/branches/");
		url.append(branchName[tempChoiceBranch]);

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

std::string Branch::getName() const{
	return this->name;
}

void Branch::setName(std::string name){
    this->name = name;
}

Branch::~Branch() {
	// TODO Auto-generated destructor stub
}

Branch::Branch(const Branch &other) {
	// TODO Auto-generated constructor stub

}

