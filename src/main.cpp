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
	int fd[2];

	while(1) {
		cmd.clear();
		cmdLine = oShell.readCmd();
		cmd = oShell.parseCmd(cmdLine);
		oShell.run(cmd, fd);
	}

	return 0;
}