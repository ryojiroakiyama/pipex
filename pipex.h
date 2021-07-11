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

char	**g_command;
char	*g_path;
int		g_pipefd[2];

#endif
