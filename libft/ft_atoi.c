/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:29:22 by takataok          #+#    #+#             */
/*   Updated: 2021/04/19 20:44:29 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	checkover(long ans, int digit)
{
	if (ans <= (LONG_MAX - digit) / 10)
		return (ans);
	else
		return (-1);
}

static long	getnumber(const char *str, int *num, long a, int sign)
{
	int	i;

	i = 0;
	while (str[*num + i] <= '9' && str[*num + i] >= '0')
	{
		a = checkover(a, str[*num + i] - '0');
		if (a == -1)
			break ;
		a = a * 10 + str[*num + i] - '0';
		i++;
	}
	if (sign == 1 && a != -1)
		return (a * -1);
	else if (sign == 1)
		return (0);
	else
		return (a);
}

int	ft_atoi(const char *str)
{
	long	a;
	int		i;
	int		sign;

	a = 0;
	i = 0;
	sign = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign += 1;
		i++;
	}
	a = getnumber(str, &i, a, sign);
	return ((int)a);
}
