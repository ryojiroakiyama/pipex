#include "./pipex.h"

char **g_command;
char *g_path;

/*
void end(void)__attribute__((destructor));

void end(void)
{
    system("leaks pipex");
}
*/
void free_2d_array(char **array)
{
	size_t i;

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

void free_1d_array(char *array)
{
	if (array == NULL)
		return ;
	free(array);
	array = NULL;
}

void put_2d_array(char **a)
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

void ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	free_2d_array(g_command);
	free_1d_array(g_path);
	exit(1);
}

void perrexit(const char *s)
{
	perror(s);
	free_2d_array(g_command);
	free_1d_array(g_path);
	exit(1);
}

char *verify_1d_array(char *array, char *to_free1, char **to_free2)
{
	if (!array)
	{
		free_1d_array(to_free1);
		free_2d_array(to_free2);
		perrexit("malloc");
	}
	return (array);
}

char **verify_2d_array(char **array)
{
	if (!array)
		perrexit("malloc");
	return (array);
}

char *get_path(char *command, char **envp)
{
	size_t	i;
	char	*tmp1;
	char	*tmp2;
	char	**path_list;

	i = 0;
	path_list = verify_2d_array(ft_split((*envp) + 5, ':'));
	while (path_list[i])
	{
		tmp1 = verify_1d_array(ft_strjoin(path_list[i], "/"), NULL, path_list);
		tmp2 = verify_1d_array(ft_strjoin(tmp1, command), tmp1, path_list);
		free_1d_array(tmp1);
		if (access(tmp2, F_OK | X_OK) == 0)
		{
			free_2d_array(path_list);
			return (tmp2);
		}
		free_1d_array(tmp2);
		i++;
	}
	free_2d_array(path_list);
	return (NULL);
}

void set_command(char *av_command, char **envp)
{
	g_command = verify_2d_array(ft_split(av_command, ' '));
	g_path = NULL;
	if (access(g_command[0], F_OK | X_OK) == 0)
		g_path = verify_1d_array(ft_strdup(g_command[0]), NULL, NULL);
	else
	{
		while (*envp && ft_strncmp(*envp, "PATH=", 5))
			envp++;
		if (*envp != NULL)
			g_path = get_path(g_command[0], envp);
	}
	if (g_path == NULL)
		ft_exit("no such file or permission denied");
}

void first_section(char **av, char **envp)
{
	int infilefd;

	set_command(av[2], envp);
	infilefd = open(av[1], O_RDONLY);
	if (infilefd == -1)
		perrexit("open");
	dup2(infilefd, 0);
	execve(g_path, g_command, envp);
	free_2d_array(g_command);
	free_1d_array(g_path);
	close(infilefd);
}

void next_section(char **av, char **envp)
{
	int outfilefd;

	set_command(av[3], envp);
	outfilefd = open(av[4], O_RDWR | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	if (outfilefd == -1)
		perrexit("open");
	dup2(outfilefd, 1);
	execve(g_path, g_command, envp);
	free_2d_array(g_command);
	free_1d_array(g_path);
	close(outfilefd);
}

int	main(int ac, char **av, char **envp)
{
	int pid;
	int	status;

	if (ac != 5)
		ft_exit("invalid number of arguments");
	pid = fork();
	if (pid == -1)
		perrexit("fork");
	else if (pid == 0)
		first_section(av, envp);
	else
	{
		if (wait(&status) == -1)
			perrexit("wait");
		if (WEXITSTATUS(status) == 0)
			next_section(av, envp);
		else
			exit(1);
	}
	return (0);
}
