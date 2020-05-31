/*
 * Utils.cpp
 *
 *  Created on: 29 Apr 2020
 *      Author: nmiha
 */

#include "Utils.h"

struct MemoryStruct {
	char* memory;
	size_t size;
};

static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp){
	size_t realSize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct *)userp;

	char* ptr = (char*) realloc(mem->memory, mem->size + realSize + 1);

	if(ptr == nullptr){
		printf("Not enought memory(realloc returned NULL)\n");
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realSize);
	mem->size += realSize;
	mem->memory[mem->size] = 0;

	return realSize;
}

Utils::Utils() {
	// TODO Auto-generated constructor stub
}

void Utils::login() const{
	std::cout << std::endl << "	  LOGIN" << std::endl;
	std::cout << "  1- Log in / 2- Exit" << std::endl;
	std::cout << "--------------------------" << std::endl;
}

void Utils::subMenu() const{
		std::cout << std::endl <<  "-------------------------------" << std::endl;
		std::cout << "	    MENU:" << std::endl;
		std::cout << "Groups Management" << std::endl;
		std::cout << "  1- New Group" << std::endl;
		std::cout << "  2- Delete Group" << std::endl;
		std::cout << "  3- Show Groups" << std::endl;
		std::cout << "Project Management" << std::endl;
		std::cout << "  4- New Project" << std::endl;
		std::cout << "  5- All user projects(owner + member)" << std::endl;
		std::cout << "  6- User project list(owner)" << std::endl;
		std::cout << "  7- GET for a specific project" << std::endl;
		std::cout << "  8- Delete  project" << std::endl;
		std::cout << "Branch Management" << std::endl;
		std::cout << "  9- New branch" << std::endl;
		std::cout << "  10- Show all branches for a specific repository" << std::endl;
		std::cout << "  11- Delete branch" << std::endl;
		std::cout << "  12- Back to Log in" << std::endl;
}

	//Save the current user
    User user;

void Utils::loginMenu(){
	int loginChoice;

	do{
		//Login Menu
		login();

		std::cout<< "Your choice: ";
		std::cin >> loginChoice;
		std::cout << std::endl;

		switch(loginChoice){
		case 1:
			//Set username&password
			user.signIn();

			//Generate and transfer Token
			setAccessToken(user.generateToken());
			try{
				if(getAccessToken() == "Username or password is incorrect!"){
					throw std::string("Username or password is incorrect!");
				}

				operationsMenu();

			}catch(std::string& e){
				std::cout << e;
			}
			break;
		case 2:
			break;
		default:
			std::cout << "Please try again!" << std::endl;
			break;
		}
	}while(loginChoice != 2);
}

void Utils::operationsMenu(){
	Group group;
	Project project;
	Branch branch;

    std::vector<std::string> tempGroupList;
    std::vector<std::string> tempProjectList;
    std::vector<std::string> tempBranchList;
    int menuChoice, tempDel, tempChoiceProject, tempChoiceBranch;
    std::string tempName, tempSelectedProjectId;
    std::string username = user.getUsername();

	do{
		//Show the menu
		subMenu();

		std::cout << "Your choice:";
		std::cin >> menuChoice;
		std::cout << std::endl;

		switch(menuChoice){
		case 1:
			if(!group.isDataOk()){
				break;
			}

			try{
				std::string receivedMessage = group.createGroup(getAccessToken());
				if(receivedMessage == "The group was created!")
				{
					throw std::string("The group was created!");
				}

				std::cout << std::endl;

				throw std::string(receivedMessage);
			}catch(std::string& e){
				std::cout << e << std::endl;
			}
			break;
        case 2:
            std::cout << "Al Groups:" << std::endl;
            tempGroupList.clear();
            tempGroupList = group.groupList(getAccessToken());

            for(unsigned long i = 0; i < tempGroupList.size(); i++){
                std::cout << i << ": "<< tempGroupList.at(i) << std::endl;
            }

            std::cout << "Select a Group: ";
            std::cin >> tempDel;
            group.setChoiceDelete(tempDel);

			group.deleteGroup(getAccessToken());
			break;
		case 3:
            tempGroupList.clear();
            tempGroupList = group.groupList(getAccessToken());

            std::cout << std::endl << "Group List" << std::endl;
            for(unsigned long i = 0; i < tempGroupList.size(); i++){
                std::cout << i << ": "<< tempGroupList.at(i) << std::endl;
            }
			break;
		case 4:
			project.setData();

			try{
				std::string receivedMessage = project.createProject(getAccessToken());
				if(receivedMessage == "The group was created!")
				{
					throw std::string("The group was created!");
				}

				std::cout << std::endl;

				throw std::string(receivedMessage);
			}catch(std::string& e){
				std::cout << e << std::endl;
			}
			break;
		case 5:
			project.membershipProjectList(getAccessToken(), username);
			break;
		case 6:
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "Project List" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }
			break;
		case 7:
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "All Projects:" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }

            std::cout << "Select a Project: ";
            std::cin >> tempChoiceProject;

            project.getProject(getAccessToken(), username, tempChoiceProject);
			break;
		case 8:
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "All Projects:" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }

            std::cout << "Select a Project: ";
            std::cin >> tempChoiceProject;

            project.deleteProject(getAccessToken(), username, tempChoiceProject);
			break;
		case 9:
			//Show projectList
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "All Projects:" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }

            std::cout << std::endl << "Select a project: ";
            std::cin >> tempChoiceProject;

            std::cin.ignore(256, '\n');
            std::cout << "Branch name: ";
            std::getline(std::cin, tempName);
            branch.setName(tempName);
            tempSelectedProjectId = project.getProjectId()[tempChoiceProject];

            try{
                int temp = branch.newBranch(getAccessToken(), tempSelectedProjectId);
				if(temp)
				{
					throw std::string("The Branch couldn't be created!");
				}

				std::cout << std::endl;

				throw std::string("The Branch was created!");
			}catch(std::string& e){
			std::cout << e << std::endl;
            }
			break;
		case 10:
            //Show projectList
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "All Projects:" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }

            std::cout << std::endl << "Select a project: ";
            std::cin >> tempChoiceProject;
            tempSelectedProjectId = project.getProjectId()[tempChoiceProject];

            //Show branchList
            tempBranchList.clear();
            tempBranchList = branch.branchList(getAccessToken(), tempSelectedProjectId);

            std::cout << std::endl << "Branch list:" << std::endl;
            for(unsigned long i = 0; i < tempBranchList.size(); i++){
                std::cout << i << ": "<< tempBranchList.at(i) << std::endl;
            }
			break;
		case 11:
            //Show projectList
            tempProjectList.clear();
            tempProjectList = project.projectList(getAccessToken(), username);

            std::cout << std::endl << "All Projects:" << std::endl;
            for(unsigned long i = 0; i < tempProjectList.size(); i++){
                std::cout << i << ": "<< tempProjectList.at(i) << std::endl;
            }

            std::cout << std::endl << "Select a project: ";
            std::cin >> tempChoiceProject;

            tempSelectedProjectId = project.getProjectId()[tempChoiceProject];
            branch.branchList(getAccessToken(), tempSelectedProjectId);

            //Show branchList
            tempBranchList.clear();
            tempBranchList = branch.branchList(getAccessToken(), tempSelectedProjectId);
            std::cout << std::endl << "Branch list:" << std::endl;
            for(unsigned long i = 0; i < tempBranchList.size(); i++){
                std::cout << i << ": "<< tempBranchList.at(i) << std::endl;
            }

            std::cout<<"\nSelect a branch to delete:";
            std::cin >> tempChoiceBranch;

            branch.deleteBranch(getAccessToken(), tempSelectedProjectId, tempChoiceBranch);
			break;
		case 12:
			break;
		default:
			std::cout << "Please try again!" << std::endl;
			break;
		}
	}while(menuChoice != 12);
}

Json::Value Utils::jsonData(CURL* gitPlugin){
	CURLcode res;

	struct MemoryStruct chunk;
	chunk.memory = (char*) malloc(1);
	chunk.size = 0;	

	curl_easy_setopt(gitPlugin, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(gitPlugin, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(gitPlugin, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	res = curl_easy_perform(gitPlugin);

	if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return false;
	}else{
		std::string tempChunkMemory = chunk.memory;
		Json::Value jsonData = stringToJson(tempChunkMemory);

		if(jsonData == false)
		{
			//Clean gitPlugin
			curl_easy_cleanup(gitPlugin);

			return false;
		}else
		{
			return jsonData;
		}
	}

	//Clean gitPlugin
	curl_easy_cleanup(gitPlugin);

	return false;
}

Json::Value Utils::stringToJson(const std::string &tempChunkMemory){
	//Parse response to json_File and after that extract the necessary info
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();
	Json::Value jsonData;
	std::string errors;

	bool parsingSuccessful = reader->parse(
		tempChunkMemory.c_str(),
		tempChunkMemory.c_str() + tempChunkMemory.size(),
	    &jsonData,
	    &errors
	);

	if (!parsingSuccessful) {
	    std::cout << "Failed to parse the JSON, errors:" << std::endl;
	    std::cout << errors << std::endl;
	    return false;
	}else
	{
		return jsonData;
	}

	return false;
}

void Utils::setAccessToken(std::string accessToken){
    Utils::accessToken = accessToken;
}

std::string Utils::getAccessToken() const{
    return Utils::accessToken;
}

Utils::~Utils() {
	// TODO Auto-generated destructor stub
}

Utils::Utils(const Utils &other) {
	// TODO Auto-generated constructor stub

}
