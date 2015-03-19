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
	vector<string> cmdCur;
	int head;
	int input, output, fd[2];

	while(1) {
		cmd.clear();
		cmdLine = oShell.readCmd();
		cmd = oShell.parseCmd(cmdLine);

		head = 0;
		input = STDIN_FILENO;
		pipe(fd);
		
		while(head < cmd.size()) {
			/* tokenize pipe command */
			cmdCur.clear();
			while(head < cmd.size() && cmd[head] != "|") {
				cmdCur.push_back(cmd[head++]);
			}

			if (head < cmd.size()) {
				head++;			/* skip "|" */
				output = fd[WRITE];
			} else
				output = STDOUT_FILENO;

			if(oShell.isBuiltInCmd(cmdCur)) {
				oShell.execBuiltInCmd(cmdCur);
			} else {
				oShell.caller(input, output, cmdCur);
			}

			input = fd[READ];
		}
	}

	return 0;
}