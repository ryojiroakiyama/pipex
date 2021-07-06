/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:42:50 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 17:06:31 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		if (((unsigned char *)src)[count] == (unsigned char)c)
			break ;
		count++;
	}
	if (count == n)
		return (0);
	return (&((unsigned char *)src)[count]);
}
