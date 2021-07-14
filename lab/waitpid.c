
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int	status;
	pid_t w_pid;
	int p_max = 3;
	int	pid_list[p_max];
	int	i = 0;

	printf("start\n");
	while(i < p_max)
	{
		pid_list[i] = fork();
		if (pid_list[i] == -1)
		{
			printf("fork error\n");
			exit(1);
		}
		else if (pid_list[i] == 0)
		{
			printf("pid = %d\n", getpid());
			printf("child process:i->%d\n", i);
			sleep(1);
			if (i < 2)
				exit(0);
			exit(100);
		}
		i++;
		printf("end of while\n");
	}
	printf("after fork-while\n");
	w_pid = waitpid(pid_list[p_max - 1], &status, 0);
	printf("after wait\n");
	printf("w_pid->%d\n", (int)w_pid);
	if (w_pid < 0)
	{
		printf("wait error\n");
		exit(-1);
	}
	//		if (WIFEXITED(status))
	//			printf("child process exited : exit status->%d\n", WEXITSTATUS(status));
	//		else
	//			printf("wait false : exit status->%d\n", status);
	//		if (WIFSIGNALED(status))
	//			printf("child process exited by signal->%d\n", WTERMSIG(status));
	printf("child exit status->%d\n", WEXITSTATUS(status));
	printf("end\n");
	return (0);
}
