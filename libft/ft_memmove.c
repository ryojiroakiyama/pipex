/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:08:32 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 15:47:26 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	count;

	if (dest <= src)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		count = n;
		while (count != 0)
		{
			count--;
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		}
	}
	return (dest);
}
