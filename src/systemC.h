/* File		: systemC.h							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class systemC{
public:
	systemC();
	virtual ~systemC();
	string currentUser();
	string currentHost();
	string currentDirectory();
	string userHome();
	void changeDirectory(string path);
	vector<int> jobList;
};

#define Clear		"\033c";

systemC::systemC(){
}
systemC::~systemC(){
}
string systemC::currentDirectory(){
	string out = getcwd(NULL, 0);
	if (out.substr(0, userHome().length()) == userHome()){
		out = "~" + out.erase(0, userHome().length());
		return out;
	} else{
		return out;
	}
}
string systemC::currentUser(){
	return getlogin();
}
string systemC::currentHost(){
	char buf[32];
	int out = gethostname(buf, sizeof buf);
	if (out == -1){
		return "localhost";
	} else{
		return buf;
	}
}
string systemC::userHome(){
	return getenv("HOME");
}
void systemC::changeDirectory(string path){
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

#endif