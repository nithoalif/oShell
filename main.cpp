/* File		: main.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/
#include <iostream>
#include <vector>
#include <sys/wait.h>
#include "shellC.h"
using namespace std;

int main(int argc, char const *argv[]){
	cout << Clear;
	shellC oShell;
	vector<string> cmd;
	string cmdLine;
	int status;
	while(1){
		cmd.clear();
		cmdLine = oShell.readCmd();
		cmd = oShell.parseCmd(cmdLine);
		if(oShell.isBuiltInCmd(cmd)){
			oShell.execBuiltInCmd(cmd);
		} else{
			pid_t pid = fork();
			if(pid == 0){
				oShell.execExternCmd(cmd);
			} else{
				wait(&status);				
			}
		}
	}

	return 0;
}