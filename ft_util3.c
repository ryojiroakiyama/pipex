/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:40:19 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 21:42:42 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_1_c(int pipe_fd[2])
{
	char	*tmp_cmd1;
	char	**all_cmd;
	int		in_fd;

	close(pipe_fd[0]);
	in_fd = open(g_argv[1], O_RDONLY);
	if (in_fd == -1)
		ft_perror_exit(g_argv[1]);
	if (dup2(pipe_fd[1], 1) == -1 || dup2(in_fd, 0) == -1)
		ft_perror_exit("dup");
	all_cmd = ft_split(g_argv[2], ' ');
	if (all_cmd == NULL)
		ft_perror_exit("malloc");
	tmp_cmd1 = ft_search_cmd(all_cmd[0]);
	if (tmp_cmd1 == NULL)
	{
		ft_clear_2array(all_cmd);
		ft_perror_exit("malloc");
	}
	all_cmd[0] = tmp_cmd1;
	if (execve(all_cmd[0], all_cmd, g_envp) == -1)
		ft_perror_exit_cmd(all_cmd);
	exit (0);
}

void	ft_cmd_2_c(int pipe_fd[2], int new_pipe_fd[2])
{
	char	*tmp_cmd1;
	char	**all_cmd;

	close(new_pipe_fd[0]);
	if (dup2(pipe_fd[0], 0) == -1 || dup2(new_pipe_fd[1], 1) == -1)
		ft_perror_exit("dup");
	all_cmd = ft_split(g_argv[3], ' ');
	if (all_cmd == NULL)
		ft_perror_exit("malloc");
	tmp_cmd1 = ft_search_cmd(all_cmd[0]);
	if (tmp_cmd1 == NULL)
	{
		ft_clear_2array(all_cmd);
		ft_perror_exit("malloc");
	}
	all_cmd[0] = tmp_cmd1;
	if (execve(all_cmd[0], all_cmd, g_envp) == -1)
		ft_perror_exit_cmd(all_cmd);
	exit (0);
}
