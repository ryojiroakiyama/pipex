/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 22:16:15 by takataok          #+#    #+#             */
/*   Updated: 2021/04/11 20:40:49 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstmap_check_null(void *contentpoint, t_list *newlst, \
void (*del)(void *))
{
	if (contentpoint == NULL)
	{
		if (del == NULL)
			return (1);
		ft_lstclear(&newlst, del);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	void	*contentpoint;

	if (lst == NULL || f == NULL)
		return (NULL);
	contentpoint = f(lst->content);
	if (contentpoint == NULL)
		return (NULL);
	newlst = ft_lstnew(contentpoint);
	if (newlst == NULL)
		return (NULL);
	lst = lst->next;
	while (lst != NULL)
	{
		contentpoint = f(lst->content);
		if (ft_lstmap_check_null(contentpoint, newlst, del))
			return (NULL);
		contentpoint = ft_lstnew(contentpoint);
		if (ft_lstmap_check_null(contentpoint, newlst, del))
			return (NULL);
		ft_lstadd_back(&newlst, contentpoint);
		lst = lst->next;
	}
	return (newlst);
}
