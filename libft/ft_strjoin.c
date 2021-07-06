/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:05:08 by takataok          #+#    #+#             */
/*   Updated: 2021/04/13 16:52:42 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*com_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	com_str = (char *)ft_calloc((ft_strlen(s1) + \
		ft_strlen(s2) + 1), sizeof(char));
	if (com_str == NULL)
		return (NULL);
	com_str = ft_strcat(com_str, s1);
	com_str = ft_strcat(com_str, s2);
	return (com_str);
}
