#include "pipex.h"

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
