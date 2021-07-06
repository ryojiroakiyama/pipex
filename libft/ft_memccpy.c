/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 09:08:32 by takataok          #+#    #+#             */
/*   Updated: 2021/04/19 21:36:41 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		if (((unsigned char *)src)[count] == (unsigned char)c)
			break ;
		count++;
	}
	if (count == n)
		return (NULL);
	return (&((unsigned char *)dest)[count + 1]);
}
