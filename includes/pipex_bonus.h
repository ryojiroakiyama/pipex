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

enum e_pipefd
{
	READ,
	WRITE,
	PIPEFD_NUM
};

enum e_index
{
	START,
	STOP,
	NOW,
	HERE_DOC,
	INDEX_NUM
};

char	**g_path_list;
char	**g_cmd;
char	*g_cmd_path;
/*
void	first_section(char **av, char **envp);
void	next_section(char **av, char **envp);
void	set_path_list(char **envp);
int		main(int ac, char **av, char **envp);

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
int		get_next_line(int fd, char **line);

#endif
