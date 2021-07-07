#include "./pipex.h"

char **g_command;
char *g_path;


void end(void)__attribute__((destructor));

void end(void)
{
    system("leaks pipex");
}


void free_2d_array(char **a)
{
	size_t i;

	i = 0;
	while (a[i] != NULL)
	{
		free(a[i]);
		i++;
	}
	free(a);
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
	exit(1);
}

void perrexit(const char *s)
{
	perror(s);
	exit(1);
}

char *get_path(char *command, char **envp)
{
	size_t	i;
	char	*tmp1;
	char	*tmp2;
	char	**path_list;

	i = 0;
	path_list = ft_split((*envp) + 5, ':');
	while (path_list[i])
	{
		tmp1 = ft_strjoin(path_list[i], "/");
		tmp2 = ft_strjoin(tmp1, command);
		free(tmp1);
		if (access(tmp2, F_OK | X_OK) == 0)
		{
			free_2d_array(path_list);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	free_2d_array(path_list);
	return (NULL);
}

void set_command(char *av_command, char **envp)
{
	g_command = ft_split(av_command, ' ');
	g_path = NULL;
	if (access(g_command[0], F_OK | X_OK) == 0)
		g_path = ft_strdup(g_command[0]);
	else
	{
		while (*envp && ft_strncmp(*envp, "PATH=", 5))
			envp++;
		if (*envp != NULL)
			g_path = get_path(g_command[0], envp);
	}
	if (g_path == NULL)
	{
		free_2d_array(g_command);
		ft_exit("no such file or permission denied");
	}
}
		
int	main(int ac, char **av, char **envp)
{
	(void)ac;
//	if (ac != 5)
//		ft_exit("invalid number of arguments");
	set_command(av[1], envp);//challege with ls as av[1]
	put_2d_array(g_command);
	printf("%s\n", g_path);
	free_2d_array(g_command);
	free(g_path);
	return (0);
}
