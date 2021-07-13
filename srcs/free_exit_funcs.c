#include "pipex.h"

void	free_2d_array(char ***array)
{
	size_t	i;

	if (*array == NULL)
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_1d_array(char **array)
{
	if (*array == NULL)
		return ;
	free(*array);
	*array = NULL;
}

void	ft_exit(int status)
{
	if (status == INVALID_ARGC)
		ft_putendl_fd("invalid number of arguments", 2);
	if (status == F_OK_X_NO)
		ft_putendl_fd("command : permission denied", 2);
	if (status == F_NO_X_NO)
		ft_putendl_fd("command not found", 2);
	free_2d_array(&g_command);
	free_1d_array(&g_path);
	close(g_pipefd[READ]);
	close(g_pipefd[WRITE]);
	exit(status);
}

void	perrexit(const char *s, int status)
{
	perror(s);
	free_2d_array(&g_command);
	free_1d_array(&g_path);
	close(g_pipefd[READ]);
	close(g_pipefd[WRITE]);
	exit(status);
}
