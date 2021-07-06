/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 22:23:38 by takataok          #+#    #+#             */
/*   Updated: 2021/04/11 00:08:40 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*c_point;

	c_point = lst;
	if (lst == NULL)
		return (c_point);
	while (c_point->next != NULL)
	{
		c_point = c_point->next;
	}
	return (c_point);
}
