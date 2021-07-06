/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:45:46 by takataok          #+#    #+#             */
/*   Updated: 2021/04/07 15:56:15 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t num)
{
	size_t	count;

	count = 0;
	while (count < num)
	{
		((unsigned char *)str)[count] = '\0';
		count++;
	}
}
