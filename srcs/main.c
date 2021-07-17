#include "pipex.h"

void	first_section(char **av, char **envp)
{
	int	infilefd;

//	infilefd = open(av[1], O_RDONLY);
	infilefd = open(av[1], O_RDONLY | O_NONBLOCK);
	if (infilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(infilefd, STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(infilefd);
	close(g_pipefd[READ]);
	if (dup2(g_pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(g_pipefd[WRITE]);
	set_cmd_cmdpath(av[2]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	next_section(char **av, char **envp)
{
	int	outfilefd;

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
	set_cmd_cmdpath(av[3]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	set_path_list(char **envp)
{
	size_t	i;
	char	*tmp;

	while (*envp && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
		return ;
	g_path_list = ft_split((*envp) + 5, ':');
	if (!g_path_list)
		perrexit("malloc", EXIT_FAILURE);
	i = 0;
	while (g_path_list[i])
	{
		tmp = g_path_list[i];
		g_path_list[i] = ft_strjoin(g_path_list[i], "/");
		free(tmp);
		if (!g_path_list[i])
			perrexit("malloc", EXIT_FAILURE);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	int	pid;
	int	status;

	if (ac != 5)
		ft_exit(INVALID_ARGC);
	set_path_list(envp);
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
		next_section(av, envp);
	}
	return (0);
}
