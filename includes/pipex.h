#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# define INVALID_ARGC 1
# define F_OK_X_OK 0
# define F_OK_X_NO 126
# define F_NO_X_NO 127
# define READ 0
# define WRITE 1

char	**g_path_list;
char	**g_cmd;
char	*g_cmd_path;
int		g_pipefd[2];

//char	**g_command;
//ar	*g_path;
//int		g_pipefd[2];
/*
typedef struct s_fd
{
	int	infd;
	int	outfd;
}	t_fd;
*/

void	first_section(char **av, char **envp);
void	next_section(char **av, char **envp);
void	set_path_list(char **envp);
int		main(int ac, char **av, char **envp);
/*
char	*verify_1d_array(char *array, char **to_free1, \
							char ***to_free2, int status);
char	**verify_2d_array(char **array, int status);
*/
int		verify_access(char *file);
int		get_cmd_path(char *cmd, int status);
void	set_cmd_cmdpath(char *av_cmd);

void	free_2d_array(char ***array);
void	free_1d_array(char **array);
void	ft_exit(int status);
void	perrexit(const char *s, int status);

#endif
