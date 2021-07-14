#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 5

int main(int argc, char **argv)
{
	int		pipefd[2];
	int		p_id;
	int		status;
	char	buff[BUFF_SIZE];
	int		cnum;

	if (argc != 2)
	{
		printf("argc error\n");
		exit (1);
	}
	if (pipe(pipefd) == -1)
	{
		printf("pipe false\n");
		exit (1);
	}
	p_id = fork();
	if (p_id == -1)
	{
		printf("fork false\n");
		exit (1);
	}
	else if (p_id == 0)
	{
		close(pipefd[1]);//close no use fd
		while ((cnum = read(pipefd[0], &buff, BUFF_SIZE)) > 0)
			write(1, buff, cnum);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);//close no use fd
		write(pipefd[1], argv[1], strlen(argv[1]) + 1);
		close(pipefd[1]);
		wait(&status);
	}
	return (0);
}		
