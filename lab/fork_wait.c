#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int pid;
	int	status;
	pid_t result;

	printf("start\n");
	pid = fork();
	printf("after fork\n");
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		printf("child process\n");
		sleep(1);
		exit(127);
	}
	else
	{
		printf("parent process : return of pid->%d\n", pid);
		result = wait(&status);
		printf("after wait\n");
		printf("return of wait->%d\n", (int)result);
		if (result < 0)
		{
			printf("wait error\n");
			exit(-1);
		}
		if (WIFEXITED(status))
			printf("child process exited : exit status->%d\n", WEXITSTATUS(status));
		else
			printf("wait false : exit status->%d\n", status);
		if (WIFSIGNALED(status))
			printf("child process exited by signal->%d\n", WTERMSIG(status));
		printf("parent process exited\n");
	}
	printf("end\n");
	return (0);
}