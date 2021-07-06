/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:08:32 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 15:57:43 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;

	count = 0;
	if (n == 0 || dest == src)
		return (dest);
	else
	{
		while (count < n)
		{
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
			count++;
		}
	}
	return (dest);
}
