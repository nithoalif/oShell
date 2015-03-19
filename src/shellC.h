/* File		: shellC.h							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/
#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "systemC.h"

#define READ 	0
#define WRITE 	1

using namespace std;

class shellC
{
public:
	shellC();
	virtual ~shellC();
	string printPrompt();
	string readCmd();
	vector<string> parseCmd(string cmdLine);
	bool isBuiltInCmd(vector<string> cmd);
	void execBuiltInCmd(vector<string> cmd);
	void execExternCmd(vector<string> cmd);
	void caller(int in, int out, vector<string>& cmd);

private:
	systemC userSystem;
};

shellC::shellC(){}
shellC::~shellC(){}

string shellC::printPrompt(){
	return userSystem.currentUser() + "@" + userSystem.currentHost() + ":" + userSystem.currentDirectory() + " (~0_0)~ ";
}
string shellC::readCmd(){
	string out;
	out = readline(printPrompt().c_str());
	if (out[0]!=0){
		add_history(out.c_str());
	}
	return out;
}
vector<string> shellC::parseCmd(string cmdLine){
	vector<string> out;
	if (cmdLine != ""){
		size_t start=cmdLine.find_first_not_of(" "), end=start;
		while (start != string::npos){
			end = cmdLine.find(" ", start);
			out.push_back(cmdLine.substr(start, end-start));
			start = cmdLine.find_first_not_of(" ", end);
		}
	} else{
		out.push_back("");
	}
	return out;
}
bool shellC::isBuiltInCmd(vector<string> cmd){
	if (cmd[0]=="exit" || cmd[0]=="cd" || cmd[0]=="jobs" || cmd[0]=="fg"){
		return true;
	} else{
		return false;
	}
}
void shellC::execBuiltInCmd(vector<string> cmd){
	if (cmd[0] == "exit"){
		exit(EXIT_SUCCESS);
	} else if(cmd[0] == "cd"){
		userSystem.changeDirectory(cmd[1]);
	} else if(cmd[0] == "jobs"){
		/*string proc_name;
		for(int i=0; i<userSystem.jobList.size(); i++){
			proc_name = 
			cout << "[" << i << "]" << 
		}*/
	} else if(cmd[0] == "fg"){

	}
}
void shellC::execExternCmd(vector<string> cmd){
	if(cmd[0]!=""){
		vector<char*> argv;
		for(int i=0; i<cmd.size(); i++){
			argv.push_back(const_cast<char *>(cmd[i].c_str()));
		}
		argv.push_back(NULL);
		vector<string>::iterator redirout = find(cmd.begin(), cmd.end(), ">");
		if (redirout!=cmd.end()){
			int out = distance(cmd.begin(), redirout) + 1;
			freopen(cmd[out].c_str(), "w", stdout);
			argv[out-1] = NULL;
		}
		vector<string>::iterator redirin = find(cmd.begin(), cmd.end(), "<");
		if (redirin!=cmd.end()){
			int in = distance(cmd.begin(), redirin) + 1;
			freopen(cmd[in].c_str(), "r", stdin);
			argv[in-1] = NULL;
		}
		int errexec = execvp(argv[0], &argv[0]);
		if(errexec == -1){
			cout << cmd[0] << ": No such file or directory." << endl;
		}
	}
}

void shellC::caller (int in, int out, vector<string>& cmd)
{
	pid_t childpid;
	if ((childpid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}

		execExternCmd(cmd);
	}
	else
	{
		int stat;
		while(wait(&stat) != childpid);
	}
}

/*
void shellC::isBackgroundJob(){

}

void shellC::createBGJob(){
	int pid, status;
	pid = fork();
	if(!pid){
		fclose(stdin);
		fopen("/dev/null", "r");
		userSystem.jobList.push_back(getpid());
	}
	waitpid(pid, &status, 0);
}
*/

#endif