/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:17:39 by takataok          #+#    #+#             */
/*   Updated: 2021/04/08 09:36:53 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	size_t	count;

	count = 0;
	while (src[count] != '\0')
	{
		if ((unsigned char)src[count] == (unsigned char)c)
			break ;
		count++;
	}
	if (src[count] == '\0' && c != 0)
		return (0);
	return (&((char *)src)[count]);
}
