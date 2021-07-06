/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:52:21 by takataok          #+#    #+#             */
/*   Updated: 2021/04/11 00:07:50 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*point;
	t_list	*tmp;

	if (lst == NULL || del == NULL)
		return ;
	point = *lst;
	while (point != NULL)
	{
		tmp = point->next;
		ft_lstdelone(point, del);
		point = tmp;
	}
	*lst = NULL;
}
