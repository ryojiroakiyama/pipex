#include "pipex.h"
/*
char	*verify_1d_array(char *array, char **to_free1, \
							char ***to_free2, int status)
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
*/
int	verify_access(char *file)
{
	if (access(file, X_OK) == 0)
		return (F_OK_X_OK);
	if (access(file, F_OK) == 0)
		return (F_OK_X_NO);
	return (F_NO_X_NO);
}

int	get_cmd_path(char *cmd, int status)
{
	size_t	i;
	int		new_status;

	i = 0;
	while (g_path_list && g_path_list[i])
	{
		g_cmd_path = ft_strjoin(g_path_list[i], cmd);
		if (!g_cmd_path)
			perrexit("malloc", EXIT_FAILURE);
		new_status = verify_access(g_cmd_path);
		if (new_status != F_NO_X_NO)
			status = new_status;
		if (status == F_OK_X_OK)
			break ;
		free_1d_array(&g_cmd_path);
		i++;
	}
	return (status);
}

void	set_cmd_cmdpath(char *av_cmd)
{
	int	status;

	g_cmd = ft_split(av_cmd, ' ');
	if (!g_cmd)
		perrexit("malloc", EXIT_FAILURE);
	status = verify_access(g_cmd[0]);
	if (status == F_OK_X_OK)
	{
		g_cmd_path = ft_strdup(g_cmd[0]);
		if (!g_cmd_path)
			perrexit("malloc", EXIT_FAILURE);
	}
	else
		status = get_cmd_path(g_cmd[0], status);
	if (status != F_OK_X_OK)
		ft_exit(status);
}
