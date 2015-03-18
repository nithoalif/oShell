/* File		: main.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#include "shell.h"

using namespace std;

int main(int argc, char **argv){
	printf("%s", Clear);
	while (1) {
		int childPid;
		
		printPrompt();
		string cmdLine = readCmd();
		vector<string> cmd = parseCmd(cmdLine);
		if (isBuiltInCommand(cmd)){
			executeBuiltInCommand(cmd);
		} else {
			childPid = fork();
			if (childPid == 0){
				executeCommand(cmd);
				exit(0);
			} else {
				int stat;
				while (wait(&stat) != childPid);
			}

			/* else{
				if (isBackgroundJob(cmd)){

				} else{
					waitpid(childPid);
				}
			}*/
		}
	}
	puts("");
	return 0;
}

