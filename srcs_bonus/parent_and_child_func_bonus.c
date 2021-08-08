#include "pipex_bonus.h"

void	child_heredoc(char **av, int *index, int *pipefd)
{
	int		status;
	char	*line;
	char	*limiter;

	close(pipefd[READ]);
	limiter = av[index[NOW] - 1];
	status = 1;
	while (1)
	{
		if (status == 1)
			ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		status = get_next_line(0, &line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (status == 1)
			ft_putendl_fd(line, pipefd[WRITE]);
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
		outfilefd = open(av[index[NOW] + 1], \
							O_RDWR | O_APPEND | O_CREAT, S_IREAD | S_IWRITE);
	else
		outfilefd = open(av[index[NOW] + 1], \
							O_RDWR | O_TRUNC | O_CREAT, S_IREAD | S_IWRITE);
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
	(void)status;
//	if (wait(status) == -1)
//		perrexit("wait", EXIT_FAILURE);
	close(pipefd[WRITE]);
	dup2(pipefd[READ], STDIN_FILENO);
	close(pipefd[READ]);
	if (index[HERE_DOC] == 1)
		index[HERE_DOC] = 2;
	else
		index[NOW]++;
}
