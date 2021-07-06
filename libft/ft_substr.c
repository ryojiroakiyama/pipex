/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:48:19 by takataok          #+#    #+#             */
/*   Updated: 2021/04/10 11:56:14 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str_point;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str_point = (char *)ft_calloc(1, sizeof(char));
		if (str_point == NULL)
			return (NULL);
		return (str_point);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str_point = (char *)ft_calloc(len + 1, sizeof(char));
	if (str_point == NULL)
		return (NULL);
	ft_strlcpy(str_point, &s[start], len + 1);
	return (str_point);
}
