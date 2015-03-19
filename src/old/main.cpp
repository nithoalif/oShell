/* File		: main.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#include "shell.h"

#define READ 	0
#define WRITE 	1

using namespace std;

pid_t childpid;
int input, output, fd[2];  // file descriptor 

char buf[1<<20];	// buffer

void caller (int in, int out, vector<string>& cmd)
{
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

		executeCommand(cmd);
	}
	else
	{
		int stat;
		while(wait(&stat) != childpid);
	}
}

int main(int argc, char **argv)
{
	printf("%s", Clear);

	while (true) 
	{
		printPrompt();

		string cmdLine = readCmd();
		queue<string> cmdAll = parseCmd(cmdLine);
		
		while (!cmdAll.empty())
		{
			vector<string> cmd;
			pipe(fd);

			while (!cmdAll.empty() && cmdAll.front() != "|") {
				cmd.push_back(cmdAll.front());
				cmdAll.pop();
			}
			if (!cmdAll.empty()) cmdAll.pop();

			if (cmdAll.empty())
				output = STDOUT_FILENO;
			else
				output = fd[WRITE];

			if (isBuiltInCommand(cmd))
			{
				executeBuiltInCommand(cmd);
			}
			else
			{
				caller(input, output, cmd);
			}

			close(fd[WRITE]);				
			input = fd[READ];
		}
	}
	puts("");
	return 0;
}

