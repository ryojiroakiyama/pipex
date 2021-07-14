#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int f_pid;
	int	status;
	pid_t w_pid;
	int p_max = 3;
	int	pid_list[p_max];
	int	i = 0;
	int j = 0;


	printf("start\n");
	f_pid = 1;
	while(i < p_max && f_pid != 0)
	{
		j++;
		f_pid = fork();
		printf("after fork:f_pid->%d\n", f_pid);
		pid_list[i] = f_pid;
		i++;
	}
	printf("after fork-while\n");
	if (f_pid == -1)
		printf("fork error\n");
	else if (f_pid == 0)
	{
		printf("child process:j->%d\n", j);
		sleep(1);
		if (j < 3)
			exit(0);
		exit(100);
	}
	else
	{
		printf("parent process : f_pid->%d\n", f_pid);
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
		printf("parent process exited\n");
	}
	printf("end\n");
	return (0);
}