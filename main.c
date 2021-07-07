#include "./pipex.h"

char **g_command;

void ft_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

void ft_perrexit(const char *s)
{
	perror(s);
	exit(1);
}

void extract(char *avi, char *path)
{
	char 	**path_list;
	int		flag;

	flag = 0;
	g_command = ft_split(avi, ' ');
	if (access(g_command, F_OK) == 0)
		flag++;
	else
	{
		path_list = ft_split(path, ';');
		
int	main(int ac, char **av, char **envp)
{
	size_t i;

	if (ac != 5)
		ft_exit("invalid number of arguments");
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	extract(av[1], &envp[i][5]);//challege with ls as av[1]
	return (0);
}
