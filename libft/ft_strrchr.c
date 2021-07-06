/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:39 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 21:18:07 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	size_t	count;
	char	*point;

	count = -1;
	point = NULL;
	while (src[++count] != '\0')
	{
		if ((unsigned char)src[count] == (unsigned char)c)
			point = &((char *)src)[count];
	}
	if (src[count] == '\0' && c != '\0' && point == NULL)
		return (0);
	else if (src[count] == '\0' && c == '\0')
		point = &((char *)src)[count];
	return (point);
}
