/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:24 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 17:37:22 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)s1)[count] ==
	((unsigned char *)s2)[count] && count < n - 1)
		count++;
	return (((unsigned char *)s1)[count] - ((unsigned char *)s2)[count]);
}
