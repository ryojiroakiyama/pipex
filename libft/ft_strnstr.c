/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 09:20:30 by takataok          #+#    #+#             */
/*   Updated: 2021/04/19 21:51:39 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while ((s1[i] != '\0') && i < len)
	{
		j = 0;
		if (s1[i] == s2[0])
		{
			while ((s2[j] != '\0') && (s1[i + j] == s2[j]) && i + j < len)
			{
				j++;
			}
			if (s2[j] == '\0')
			{
				return (&((char *)s1)[i]);
			}
		}
		i++;
	}
	return (NULL);
}
