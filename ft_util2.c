/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:40:19 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 21:42:42 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_search_cmd(char *cmd)
{
	int		index;
	char	*cmd_path;

	index = 0;
	if (cmd == NULL || cmd[0] == '.' || cmd[0] == '/' \
	|| g_path_list[index] == NULL)
		return (cmd);
	while (g_path_list[index] != NULL)
	{
		cmd_path = ft_strjoin_3(g_path_list[index], "/", cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		index++;
	}
	if (g_path_list[index] == NULL)
		return (cmd);
	free(cmd);
	return (cmd_path);
}

char	**ft_get_paths(char **envp)
{
	int		index;
	char	*paths;
	char	**path_list;

	index = 0;
	while (ft_strncmp(envp[index], "PATH=", 5) != 0 \
	&& envp[index])
		index++;
	if (envp[index] == NULL)
		return (NULL);
	paths = ft_strdup(&envp[index][5]);
	if (paths == NULL)
	{
		perror("malloc");
		exit(1);
	}
	path_list = ft_split(paths, ':');
	if (path_list == NULL)
	{
		free(paths);
		perror("malloc");
		exit(1);
	}
	free(paths);
	return (path_list);
}

void	ft_firstcheck(int ac, char **argv, char **envp)
{
	if (ac != 5)
	{
		ft_putendl_fd("Invalid argument", 1);
		exit (1);
	}
	g_envp = envp;
	g_argv = argv;
	g_path_list = ft_get_paths(envp);
	if (access(argv[1], R_OK) == -1)
		ft_perror_exit(argv[1]);
	if (access(argv[4], W_OK) == -1 && access(argv[4], F_OK) == 0)
		ft_perror_exit(argv[4]);
}

char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	char	*tmp_cmd1;
	char	*tmp_cmd2;

	tmp_cmd1 = ft_strjoin(str1, str2);
	if (tmp_cmd1 == NULL)
		return (NULL);
	tmp_cmd2 = ft_strjoin(tmp_cmd1, str3);
	free(tmp_cmd1);
	if (tmp_cmd2 == NULL)
		return (NULL);
	return (tmp_cmd2);
}

void	ft_c_exit(void)
{
	ft_clear_2array(g_path_list);
	exit(1);
}
