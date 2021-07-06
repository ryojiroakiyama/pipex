/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 10:49:18 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 22:01:32 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**g_path_list;
char	**g_envp;
char	**g_argv;

void	ft_cmd_2_p(int new_pipe_fd[2], pid_t new_id)
{
	int		out_fd;
	int		flag;
	char	new_tmp[100];
	int		read_count;

	flag = 0;
	waitpid(new_id, &flag, 0);
	if (flag != 0)
		ft_c_exit();
	close(new_pipe_fd[1]);
	out_fd = open(g_argv[4], O_WRONLY | O_CREAT | O_TRUNC, \
	S_IREAD | S_IWRITE);
	if (out_fd == -1)
		ft_perror_exit(g_argv[4]);
	read_count = 99;
	while (read_count == 99)
	{
		read_count = read(new_pipe_fd[0], new_tmp, 99);
		write(out_fd, new_tmp, read_count);
	}
	if (read_count == -1)
		ft_perror_exit("read");
	ft_clear_2array(g_path_list);
	return ;
}

void	ft_cmd_1_p(int pipe_fd[2], pid_t id)
{
	int		flag;
	pid_t	new_id;
	int		new_pipe_fd[2];

	flag = 0;
	waitpid(id, &flag, 0);
	if (flag != 0)
		ft_c_exit();
	close(pipe_fd[1]);
	if (pipe(new_pipe_fd) == -1)
		ft_perror_exit("pipe");
	new_id = fork();
	if (new_id < 0)
		ft_perror_exit("fork");
	if (new_id == 0)
		ft_cmd_2_c(pipe_fd, new_pipe_fd);
	else
		ft_cmd_2_p(new_pipe_fd, new_id);
}

int	main(int ac, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	id;

	ft_firstcheck(ac, argv, envp);
	if (pipe(pipe_fd) == -1)
		ft_perror_exit("pipe");
	id = fork();
	if (id < 0)
		ft_perror_exit("fork");
	if (id == 0)
		ft_cmd_1_c(pipe_fd);
	else
		ft_cmd_1_p(pipe_fd, id);
	return (0);
}
