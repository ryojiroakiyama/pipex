/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 22:11:18 by takataok          #+#    #+#             */
/*   Updated: 2021/04/11 00:09:18 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*c_point;
	int		count;

	c_point = lst;
	count = 0;
	while (c_point != NULL)
	{
		c_point = c_point->next;
		count++;
	}
	return (count);
}
