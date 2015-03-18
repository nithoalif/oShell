/* File		: main.cpp							*/
/* Author	: Afrizal Fikri (135130xx)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#include <iostream>
#include <vector>
#include "shell.h"
using namespace std;

int main(int argc, char **argv){
	cout << Clear;
	while (1){
		int childPid;
		
		printPrompt();
		string cmdLine = readCmd();
		vector<string> cmd = parseCmd(cmdLine);
		if (isBuiltInCommand(cmd)){
			executeBuiltInCommand(cmd);
		} else{
			childPid = fork();
			if (childPid == 0){
				executeCommand(cmd);
			} else{
				wait();
			}

			/* else{
				if (isBackgroundJob(cmd)){

				} else{
					waitpid(childPid);
				}
			}*/
		}
	}
	cout << endl;
	return 0;
}

