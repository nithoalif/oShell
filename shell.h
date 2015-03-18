/* File		: shell.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#ifndef SHELL_H
#define SHELL_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define Clear 			"\033c"

using namespace std;

string currentDirectory();
string currentUser();
string currentHost();
string userHome();

void changeDirectory(string& path);

void printPrompt();
string readCmd();
vector<string> parseCmd(string& cmdLine);

int isBuiltInCommand(vector<string>& cmd);
void executeBuiltInCommand(vector<string>& cmd);
void executeCommand(vector<string>& cmd);

#endif