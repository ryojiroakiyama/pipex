/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:52:07 by takataok          #+#    #+#             */
/*   Updated: 2021/04/14 12:33:51 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_digit(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_rev_str(char *tab, int size)
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
	return (tab);
}

static char	*put_str_itoa(char *numstr, int n, int sign)
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

char	*ft_itoa(int n)
{
	char	*numstr;
	int		sign;

	numstr = (char *)ft_calloc(check_digit(n) + 1, sizeof(char));
	if (numstr == NULL)
		return (NULL);
	sign = 0;
	if (n >= 0)
	{
		n *= -1;
		sign = 1;
	}
	put_str_itoa(numstr, n, sign);
	if (numstr[0] == '\0')
		numstr[0] = '0';
	return (ft_rev_str(numstr, ft_strlen(numstr)));
}
