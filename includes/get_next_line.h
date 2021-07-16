#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

size_t			gnl_strlen(char *s);
ssize_t			gnl_strchr(const char *s, int c);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_subnstr(char const *s, unsigned int start, size_t len);
char			*ft_strnjoin(char const *s1, char const *s2, size_t s2_len);
int				ft_free(char **f);
int				by_stock(char **stock, char **line);
int				prepare_mem(int sign, char **line, char **buff);
ssize_t			by_buff(char **buff, char **line, char **stock, ssize_t rc);
int				get_next_line(int fd, char **line);

#endif
