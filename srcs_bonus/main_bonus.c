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

void	execute_loop(char **av, char **envp, int *index, int *status)
{
	int	pid;
	int	pipefd[PIPEFD_NUM];

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
			parent_process(status, index, pipefd);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	status;
	int	index[INDEX_NUM];
	int child_cnt;//

	if (ac < 5)
		ft_exit(INVALID_ARGC);
	if (ft_strncmp(av[1], "here_doc", 10))
	{
		index[START] = 2;
		index[HERE_DOC] = 0;
		child_cnt = ac - 3;//
	}
	else
	{
		if (ac < 6)
			ft_exit(INVALID_ARGC);
		index[START] = 3;
		index[HERE_DOC] = 1;
		child_cnt = ac - 4;//
	}
	index[STOP] = ac - 2;
	index[NOW] = index[START];
	set_path_list(envp);
	execute_loop(av, envp, index, &status);
	while (child_cnt--)//
		wait(NULL);//
	free_2d_array(&g_path_list);
	free_2d_array(&g_cmd);
	free_1d_array(&g_cmd_path);
	return (WEXITSTATUS(status));
}
