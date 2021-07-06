/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:39:34 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 22:00:55 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clear_2array(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
	{
		free(array[index]);
		index++;
	}
	free(array);
}

void	ft_perror_exit(char *str)
{
	perror(str);
	ft_clear_2array(g_path_list);
	exit(1);
}

void	ft_perror_exit_cmd(char **array)
{
	perror(array[0]);
	ft_clear_2array(array);
	ft_clear_2array(g_path_list);
	exit(1);
}

void	ft_put_2array(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
	{
		ft_putendl_fd(array[index], 1);
		index++;
	}
}
