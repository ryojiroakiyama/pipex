/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:45:46 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 15:55:21 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int character, size_t num)
{
	size_t	count;

	count = 0;
	while (count < num)
	{
		((unsigned char *)str)[count] = (unsigned char)character;
		count++;
	}
	return (str);
}
