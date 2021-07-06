/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 12:07:36 by takataok          #+#    #+#             */
/*   Updated: 2021/04/13 10:42:01 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t num, size_t size)
{
	void	*point;

	point = (void *)malloc(num * size);
	if (point == NULL)
		return (NULL);
	ft_bzero(point, num * size);
	return (point);
}
