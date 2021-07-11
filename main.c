#include "./pipex.h"

void	free_2d_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_1d_array(char *array)
{
	if (array == NULL)
		return ;
	free(array);
	array = NULL;
}

void	put_2d_array(char **a)
{
	if (a == NULL)
	{
		printf("array is NULL");
		return ;
	}
	while (*a != NULL)
	{
		printf("%s\n", *a);
		a++;
	}
}

void	ft_exit(int status)
{
	if (status == INVALID_ARGC)
		ft_putendl_fd("invalid number of arguments", 2);
	if (status == F_OK_X_NO)
		ft_putendl_fd("command : permission denied", 2);
	if (status == F_NO_X_NO)
		ft_putendl_fd("command not found", 2);
	free_2d_array(g_command);
	free_1d_array(g_path);
	close(g_pipefd[READ]);
	close(g_pipefd[WRITE]);
	exit(status);
}

void	perrexit(const char *s, int status)
{
	perror(s);
	free_2d_array(g_command);
	free_1d_array(g_path);
	close(g_pipefd[READ]);
	close(g_pipefd[WRITE]);
	exit(status);
}

char	*verify_1d_array(char *array, char *to_free1, \
							char **to_free2, int status)
{
	if (!array)
	{
		free_1d_array(to_free1);
		free_2d_array(to_free2);
		perrexit("malloc", status);
	}
	return (array);
}

char	**verify_2d_array(char **array, int status)
{
	if (!array)
		perrexit("malloc", status);
	return (array);
}

int	verify_access(char *file)
{
	if (access(file, X_OK) == 0)
		return (F_OK_X_OK);
	if (access(file, F_OK) == 0)
		return (F_OK_X_NO);
	return (F_NO_X_NO);
}

int	get_path(char *command, char **envp, int status)
{
	size_t	i;
	char	**path_list;
	char	*add_slash;
	int		new_status;

	i = 0;
	path_list = verify_2d_array(ft_split((*envp) + 5, ':'), EXIT_FAILURE);
	while (path_list[i])
	{
		add_slash = verify_1d_array(ft_strjoin(path_list[i], "/"), \
										NULL, path_list, EXIT_FAILURE);
		g_path = verify_1d_array(ft_strjoin(add_slash, command), \
										add_slash, path_list, EXIT_FAILURE);
		free_1d_array(add_slash);
		new_status = verify_access(g_path);
		if (new_status != F_NO_X_NO)
			status = new_status;
		if (status == F_OK_X_OK)
			break ;
		free_1d_array(g_path);
		i++;
	}
	free_2d_array(path_list);
	return (status);
}

void	set_command(char *av_command, char **envp)
{
	int	status;

	g_command = verify_2d_array(ft_split(av_command, ' '), EXIT_FAILURE);
	status = verify_access(g_command[0]);
	if (status == F_OK_X_OK)
		g_path = verify_1d_array(ft_strdup(g_command[0]), \
											NULL, NULL, EXIT_FAILURE);
	else
	{
		while (*envp && ft_strncmp(*envp, "PATH=", 5))
			envp++;
		if (*envp != NULL)
			status = get_path(g_command[0], envp, status);
	}
	if (status != F_OK_X_OK)
		ft_exit(status);
}

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
