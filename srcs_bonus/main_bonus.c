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

void	child_heredoc(char **av, int *index, int *pipefd)
{
	int		status;
	char 	*line;
	char	*limiter;

	close(pipefd[READ]);
	limiter = av[index[NOW] - 1];
	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
	while (1)
	{
		status = get_next_line(0, &line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (status == 1)
		{
			ft_putendl_fd(line, pipefd[WRITE]);
			ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		}
		if (status == 0)
			ft_putstr_fd(line, pipefd[WRITE]);
		free(line);
		if (status == -1)
			perrexit("malloc", EXIT_FAILURE);
	}
	free(line);
	close(pipefd[WRITE]);
	ft_exit(EXIT_SUCCESS);
}

void	child_firstpipe(char **av, char **envp, int *index, int *pipefd)
{
	int	infilefd;

	infilefd = open(av[index[NOW] - 1], O_RDONLY);
	if (infilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(infilefd, STDIN_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(infilefd);
	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	set_cmd_cmdpath(av[index[NOW]]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	child_middlepipe(char **av, char **envp, int *index, int *pipefd)
{
	close(pipefd[READ]);
	if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(pipefd[WRITE]);
	set_cmd_cmdpath(av[index[NOW]]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	child_lastpipe(char **av, char **envp, int *index, int *pipefd)
{
	int	outfilefd;

	close(pipefd[READ]);
	close(pipefd[WRITE]);
	if (index[HERE_DOC])
		outfilefd = open(av[index[NOW] + 1], O_RDWR | O_APPEND | O_CREAT, S_IREAD | S_IWRITE);
	else
		outfilefd = open(av[index[NOW] + 1], O_RDWR | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
	if (outfilefd == -1)
		perrexit("open", EXIT_FAILURE);
	if (dup2(outfilefd, STDOUT_FILENO) == -1)
		perrexit("dup2", EXIT_FAILURE);
	close(outfilefd);
	set_cmd_cmdpath(av[index[NOW]]);
	if (execve(g_cmd_path, g_cmd, envp) == -1)
		perrexit("execve", EXIT_FAILURE);
}

void	parent_process(int *status, int *index, int *pipefd)
{
	if (wait(status) == -1)
		perrexit("wait", EXIT_FAILURE);
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
	if (index[HERE_DOC] == 1)
		index[HERE_DOC] = 2;
	else
		index[NOW]++;
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
		{
			if (index[HERE_DOC] == 1)
				child_heredoc(av, index, pipefd);
			else if (index[NOW] == index[START] && index[HERE_DOC] == 0)
				child_firstpipe(av, envp, index, pipefd);
			else if (index[NOW] == index[STOP])
				child_lastpipe(av, envp, index, pipefd);
			else
				child_middlepipe(av, envp, index, pipefd);
		}
		else
			parent_process(&status, index,  pipefd);
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
		if(ac < 6)
			ft_exit(INVALID_ARGC);
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
