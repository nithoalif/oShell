/* File		: main.cpp							*/
/* Author	: Afrizal Fikri (13513004)			*/
/* 			  Nitho Alif I. (13513072)			*/
/* 			  Fiqie Ulya Sidiastahta (13513602)	*/

#include "shell.h"

#define READ 	0
#define WRITE 	1

using namespace std;

pid_t childPid;
int fd_snd[2];  // file descriptor send
int fd_rcv[2];  // file descriptor receieve

char buf[1<<20];	// buffer

int main(int argc, char **argv)
{
	printf("%s", Clear);

	pipe(fd_snd);
	pipe(fd_rcv);

	while (true) 
	{
		printPrompt();

		string cmdLine = readCmd();
		queue<string> cmdAll = parseCmd(cmdLine);
		
		while (!cmdAll.empty())
		{
			vector<string> cmd;

			while (!cmdAll.empty() && cmdAll.front() != "|") {
				cmd.push_back(cmdAll.front());
				cmdAll.pop();
			}
			if (!cmdAll.empty()) cmdAll.pop();

			if (isBuiltInCommand(cmd))
			{
				//dup2(1, fd[0]);		/* redirect stdout to pipe-in */
				
				executeBuiltInCommand(cmd);
			}
			else
			{
				childPid = fork();
				if (childPid == 0)		/* child */
				{
					write(fd_snd[WRITE], buf, strlen(buf) + 1);

					close(fd_snd[WRITE]);
					close(fd_rcv[READ]);

					dup2(fd_rcv[WRITE], STDOUT_FILENO);		/* redirect stdout to pipe-in */
					dup2(fd_snd[READ], STDIN_FILENO);		/* redirect pipe-out to stdin */

					executeCommand(cmd);
				} 
				else 			/* parent */
				{
					int status;
					while (wait(&status) != childPid);
					//cout << "cok" << endl;

					/* redirecting */
					read(fd_rcv[READ], buf, sizeof(buf));
					puts(buf);
				}

				/* else{
					if (isBackgroundJob(cmd)){

					} else{
						waitpid(childPid);
					}
				}*/
			}
		}

		puts(buf);
	}
	puts("");
	return 0;
}

