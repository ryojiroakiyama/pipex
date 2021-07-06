/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:12:14 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 22:01:08 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>

extern char	**g_path_list;
extern char	**g_envp;
extern char	**g_argv;
void	ft_clear_2array(char **array);
void	ft_perror_exit_cmd(char **array);
void	ft_perror_exit(char *str);
void	ft_c_exit(void);
void	ft_put_2array(char **array);
char	*ft_search_cmd(char *cmd);
char	**ft_get_paths(char **envp);
void	ft_firstcheck(int ac, char **argv, char **envp);
char	*ft_strjoin_3(char *str1, char *str2, char *str3);
void	ft_cmd_1_c(int pipe_fd[2]);
void	ft_cmd_2_c(int pipe_fd[2], int new_pipe_fd[2]);
void	ft_cmd_2_p(int new_pipe_fd[2], pid_t new_id);
void	ft_cmd_1_p(int pipe_fd[2], pid_t id);

#endif
