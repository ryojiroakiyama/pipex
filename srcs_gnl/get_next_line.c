#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

int	ft_free(char **f)
{
	if (*f)
		free(*f);
	*f = NULL;
	return (-1);
}

int	by_stock(char **stock, char **line)
{
	ssize_t	nl;
	char	*tmp;

	if (!(*stock))
		return (-42);
	nl = gnl_strchr(*stock, '\n');
	if (nl != -1)
	{
		*line = ft_subnstr(*stock, 0, nl);
		if (!(*line))
			return (ft_free(stock));
		tmp = *stock;
		*stock = ft_subnstr(*stock, nl + 1, gnl_strlen(*stock) - 1 - nl);
		free(tmp);
		if (!(*stock))
			return (ft_free(line));
		return (1);
	}
	*line = *stock;
	*stock = NULL;
	return (42);
}

int	prepare_mem(int sign, char **line, char **buff)
{
	if (sign == -1 || sign == 1)
		return (sign);
	if (sign == -42)
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (-1);
		*line = (char *)malloc(sizeof(char) * 1);
		if (!(*line))
			return (ft_free(buff));
		(*line)[0] = '\0';
		sign = 42;
	}
	else if (sign == 42)
	{
		*buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*buff))
			return (ft_free(line));
	}
	return (sign);
}

ssize_t	by_buff(char **buff, char **line, char **stock, ssize_t rc)
{
	ssize_t	nl;
	char	*tmp;

	if (rc == 0)
		return (0);
	(*buff)[rc] = '\0';
	nl = gnl_strchr(*buff, '\n');
	if (nl != -1)
	{
		tmp = *line;
		*line = ft_strnjoin(*line, *buff, nl);
		free(tmp);
		if (!(*line))
			return (-1);
		*stock = ft_strnjoin(0, *buff + nl + 1, gnl_strlen(*buff) - 1 - nl);
		if (!(*stock))
			return (ft_free(line));
		return (1);
	}
	tmp = *line;
	*line = ft_strnjoin(*line, *buff, gnl_strlen(*buff));
	free(tmp);
	if (!(*line))
		return (-1);
	return (42);
}

int	get_next_line(int fd, char **line)
{
	char		*buff;
	ssize_t		rc;
	static char	*stock;
	int			sign;

	if (!line || fd < 0)
		return (ft_free(&stock));
	sign = by_stock(&stock, line);
	sign = prepare_mem(sign, line, &buff);
	if (sign == -1 || sign == 1)
		return (sign);
	while (sign == 42)
	{
		rc = read(fd, buff, BUFFER_SIZE);
		if (rc == -1)
			sign = ft_free(line);
		else
			sign = by_buff(&buff, line, &stock, rc);
	}
	free(buff);
	return (sign);
}
