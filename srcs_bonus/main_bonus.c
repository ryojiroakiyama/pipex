#include "pipex.h"

void	first_section(char **av, char **envp)
{
	int	infilefd;

	set_cmd_cmdpath(av[2]);
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
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	next_section(char **av, char **envp)
{
	int	outfilefd;

	set_cmd_cmdpath(av[3]);
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


void	parent_process(int *status, int pid, int *pipefd)
{
	if (wait(status) == -1)
		perrexit("wait", EXIT_FAILURE);
	close(pipefd[READ]);
	dup2(pipefd[WRITE], STDIN_FILENO);
	close(pipefd[WRITE]);
}

int	parent_and_child(char **av, char **envp, int *index)
{
	int	pid;
	int	status;
	int pipefd[PIPEFD_NUM];

	while (index[NOW] <= index[STOP])
	{
		if (pipe(g_pipefd) == -1)
			perrexit("pipe", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			perrexit("fork", EXIT_FAILURE);
		if (pid == 0)
			child_process(av, envp, index, pipefd);
		else
			parent_process(&status, pid, pipefd);
		index[NOW]++;
	}
	return (WEXITSTATUS(status));
}

int	main(int ac, char **av, char **envp)
{
	int	last_status;
	int	index[INDEX_NUM];

	if (ac < 5)
		ft_exit(INVALID_ARGC);
	if (ft_strncmp(av[1], "here_doc", 10))
	{
		index[NOW] = 2;
		index[STOP] = ac - 2;
		index[HERE_DOC] = 0;
	}
	else
	{
		index[NOW] = 3;
		index[STOP] = ac - 2;
		index[HERE_DOC] = 1;
	}
	set_path_list(envp);
	last_status = parent_and_child(av, envp, index);
	free_2d_array(&g_path_list);
	free_2d_array(&g_cmd);
	free_1d_array(&g_cmd_path);
	return (last_status);
}
