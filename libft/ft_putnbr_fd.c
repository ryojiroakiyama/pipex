/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:29:32 by takataok          #+#    #+#             */
/*   Updated: 2021/04/14 12:34:52 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_str_rev_str_no_malloc(char *tab, int size)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = 0;
	size -= 1;
	while (i <= size - 1)
	{
		while (j <= size - 1 - i)
		{
			tmp = tab[j];
			tab[j] = tab[j + 1];
			tab[j + 1] = tmp;
			j++;
		}
		j = 0;
		i++;
	}
}

static char	*put_str_itoa_no_malloc2(char *numstr, int n, int sign)
{
	int	digit;

	digit = 0;
	while (n != 0)
	{
		numstr[digit] = (-1 * (n % 10)) + '0';
		n /= 10;
		digit++;
	}
	if (sign == 0)
		numstr[digit] = '-';
	return (numstr);
}

static void	put_str_itoa_no_malloc1(int n, char numstr[15])
{
	int		sign;

	sign = -1;
	while (++sign < 15)
		numstr[sign] = 0;
	sign = 0;
	if (n >= 0)
	{
		n *= -1;
		sign = 1;
	}
	put_str_itoa_no_malloc2(numstr, n, sign);
	if (numstr[0] == '\0')
		numstr[0] = '0';
	put_str_rev_str_no_malloc(numstr, ft_strlen(numstr));
}

void	ft_putnbr_fd(int n, int fd)
{
	char	numstr[15];

	put_str_itoa_no_malloc1(n, numstr);
	ft_putstr_fd(numstr, fd);
}
