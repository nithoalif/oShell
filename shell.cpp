/* File		: shell.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#include "shell.h"

using namespace std;

string currentDirectory(){
	string out = getcwd(NULL, 0);
	if (out.substr(0, userHome().length()) == userHome()){
		out = "~" + out.erase(0, userHome().length());
		return out;
	} else{
		return out;
	}
	
}

string currentUser(){
	return getlogin();
}

string currentHost(){
	char buf[32];
	int out = gethostname(buf, sizeof buf);
	if (out == -1){
		return "localhost";
	} else{
		return buf;
	}
}

string userHome(){
	return getenv("HOME");
}

void changeDirectory(string& path){
	int errdir = -1;
	if(path[0] == '~'){
		string homePath = userHome() + path.substr(1,path.length());
		errdir = chdir(homePath.c_str());
	} else if(path == ".."){
		errdir = chdir("..");
	} else if(path == "."){
		errdir = 0;
	} else{
		errdir = chdir(path.c_str());
	}
	if(errdir == -1){
		cout << path << ": No such file or directory." << endl;
	}
}

void printPrompt(){
	cout << currentUser() << "@" << currentHost() << ":" << currentDirectory() << " (~0_0)~ ";
}

string readCmd(){
	string out;
	getline(cin, out);
	return out;
}

vector<string> parseCmd(string& cmdLine){
	char *cstr = new char [cmdLine.length()+1];
	strcpy(cstr, cmdLine.c_str());
	char *p = strtok(cstr, " ");
	vector<string> out;
	while (p != 0){
		out.push_back(p);
		p = strtok(NULL, " ");
	}
	delete[] cstr;
	return out;
}

int isBuiltInCommand(vector<string>& cmd){
	if (cmd[0]=="exit" || cmd[0]=="cd" || cmd[0]=="jobs" || cmd[0]=="fg"){
		return 1;	//built-in commands
	} else{
		return 0;	//not a built-in commands
	}
}

void executeBuiltInCommand(vector<string>& cmd){
	if (cmd[0] == "exit"){
		exit(EXIT_SUCCESS);
	} else if(cmd[0] == "cd"){
		changeDirectory(cmd[1]);
	} else if(cmd[0] == "jobs"){
		//ISI DEFINISI JOB
	} else if(cmd[0] == "fg"){
		//ISI DEFINISI FG
	}
}

void executeCommand(vector<string>& cmd) {
	const char** argv = new const char*[cmd.size()+1];
	for(int i=0; i<cmd.size(); i++){
		argv[i] = cmd[i].c_str();
	}
	argv[cmd.size()] = NULL;
	execvp(argv[0], (char**)argv);
	//perror(cmd[0]);
}
