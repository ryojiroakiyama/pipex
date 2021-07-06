/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:04:14 by takataok          #+#    #+#             */
/*   Updated: 2021/06/29 21:33:37 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	j = n;
	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && ((i < j - 1) && (s1[i] != '\0' && \
		s2[i] != '\0')))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
