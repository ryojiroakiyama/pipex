#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "libft.h"
# include "get_next_line.h"
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

int		verify_access(char *file);
int		get_cmd_path(char *cmd, int status);
void	set_cmd_cmdpath(char *av_cmd);
void	free_2d_array(char ***array);
void	free_1d_array(char **array);
void	ft_exit(int status);
void	perrexit(const char *s, int status);
void	child_heredoc(char **av, int *index, int *pipefd);
void	child_firstpipe(char **av, char **envp, int *index, int *pipefd);
void	child_middlepipe(char **av, char **envp, int *index, int *pipefd);
void	child_lastpipe(char **av, char **envp, int *index, int *pipefd);
void	parent_process(int *status, int *index, int *pipefd);
void	set_path_list(char **envp);
void	execute_loop(char **av, char **envp, int *index, int *status);
int		main(int ac, char **av, char **envp);

#endif
