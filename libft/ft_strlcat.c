/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:05:48 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 18:15:27 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	r;

	j = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	if (i >= size)
		r = size;
	else
	{
		r = i;
		while (s2[j] != '\0' && j < size - i - 1)
		{
			s1[i + j] = s2[j];
			j++;
		}
		s1[i + j] = '\0';
	}
	return (r + ft_strlen(s2));
}
