/* File		: shell.cpp							*/
/* Author	: Afrizal Fikri (135130xx)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/
#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#define Clear 			"\033c";

string currentDirectory();
string currentUser();
string currentHost();
string userHome();

void changeDirectory(string path);

void printPrompt();
string readCmd();
vector<string> parseCmd(string cmdLine);

int isBuiltInCommand(vector<string> cmd);
void executeBuiltInCommand(vector<string> cmd);
void executeCommand(vector<string> cmd);

#endif