#include "pipex.h"

void	first_section(char **av, char **envp)
{
	int	infilefd;

	set_command(av[2], envp);
	infilefd = open(av[1], O_RDONLY);
	if (infilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(infilefd, STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(infilefd);
	close(g_pipefd[READ]);
	if (dup2(g_pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(g_pipefd[WRITE]);
	if (execve(g_path, g_command, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	next_section(char **av, char **envp)
{
	int	outfilefd;

	set_command(av[3], envp);
	outfilefd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (outfilefd == -1)
		perrexit("open", EXIT_FAILURE);
	close(g_pipefd[WRITE]);
	if (dup2(g_pipefd[READ], STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(g_pipefd[READ]);
	if (dup2(outfilefd, STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(outfilefd);
	if (execve(g_path, g_command, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int	pid;
	int	status;

	g_command = NULL;
	g_path = NULL;
	if (ac != 5)
		ft_exit(INVALID_ARGC);
	if (pipe(g_pipefd) == -1)
		perrexit("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perrexit("fork", EXIT_FAILURE);
	else if (pid == 0)
		first_section(av, envp);
	else
	{
		if (wait(&status) == -1)
			perrexit("wait", EXIT_FAILURE);
		if (WEXITSTATUS(status) == 0)
			next_section(av, envp);
		else
			exit(WEXITSTATUS(status));
	}
	return (0);
}
