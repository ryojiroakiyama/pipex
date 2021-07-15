#include "pipex_bonus.h"

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

void	here_doc_run(char **av, char **envp, int *index, int *pipefd)
{
	
	return ;
}

void	first_run(char **av, char **envp, int *index, int *pipefd)
{
	int	infilefd;

	set_cmd_cmdpath(av[index[NOW]]);
	infilefd = open(av[index[NOW - 1]], O_RDONLY);
	if (infilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(infilefd, STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(infilefd);
	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	middle_run(char **av, char **envp, int *index, int *pipefd)
{
	set_cmd_cmdpath(av[index[NOW]]);
	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	last_run(char **av, char **envp, int *index, int *pipefd)
{
	int	outfilefd;

	set_cmd_cmdpath(av[NOW]);
	close(pipefd[WRITE]);
	if (dup2(pipefd[READ], STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(pipefd[READ]);
	outfilefd = open(av[NOW + 1], O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (outfilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(outfilefd, STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(outfilefd);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	child_processes(char **av, char **envp, int *index, int *pipefd)
{
	if (index[HERE_DOC])
		here_doc_run(av, envp, index, pipefd);
	else if (index[NOW] == index[START])
		first_run(av, envp, index, pipefd);
	else if (index[START] < index[NOW] && index[NOW] < index[STOP])
		middle_run(av, envp, index, pipefd);
	else if (index[NOW] == index[STOP])
		last_run(av, envp, index, pipefd);
	else
		perrexit("index not meet the conditions", EXIT_FAILURE);
}

void	parent_process(int *status, int *pipefd)
{
	if (waitipid(status) == -1)
		perrexit("wait", EXIT_FAILURE);
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
}

int	execute_loop(char **av, char **envp, int *index)
{
	int	pid;
	int	status;
	int pipefd[PIPEFD_NUM];

	while (index[NOW] <= index[STOP])
	{
		if (pipe(pipefd) == -1)
			perrexit("pipe", EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			perrexit("fork", EXIT_FAILURE);
		if (pid == 0)
			child_process(av, envp, index, pipefd);
		else
			parent_process(&status, pipefd);
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
		index[START] = 2;
		index[HERE_DOC] = 0;
	}
	else
	{
		index[START] = 3;
		index[HERE_DOC] = 1;
	}
	index[STOP] = ac - 2;
	index[NOW] = index[START];
	set_path_list(envp);
	last_status = execute_loop(av, envp, index);
	free_2d_array(&g_path_list);
	free_2d_array(&g_cmd);
	free_1d_array(&g_cmd_path);
	return (last_status);
}
