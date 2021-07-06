/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:12:36 by takataok          #+#    #+#             */
/*   Updated: 2021/04/14 13:27:50 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*c_point;

	if (f == NULL)
		return ;
	c_point = lst;
	while (c_point != NULL)
	{
		f(c_point->content);
		c_point = c_point->next;
	}
}
