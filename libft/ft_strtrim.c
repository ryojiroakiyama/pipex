/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 16:37:06 by takataok          #+#    #+#             */
/*   Updated: 2021/04/14 12:40:51 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set_char(const char *s1, \
const char *set, size_t s_c, size_t op)
{
	size_t	count;
	size_t	set_count;

	count = 0;
	while (s1[s_c] != '\0')
	{
		set_count = -1;
		while (set[++set_count] != '\0')
		{
			if (s1[s_c] == set[set_count])
			{
				count++;
				if (op)
					s_c++;
				else
					s_c--;
				break ;
			}
		}
		if (set[set_count] != '\0')
			continue ;
		break ;
	}
	return (count);
}

static char	*ft_strtrim_malloc_trim_str(size_t *f_c, size_t *b_c, \
char const *s1, char const *set)
{
	*f_c = check_set_char(s1, set, 0, 1);
	if (*f_c == ft_strlen(s1))
	{
		return ((char *)ft_calloc(1, 1));
	}
	*b_c = check_set_char(s1, set, ft_strlen(s1) - 1, 0);
	return ((char *)ft_calloc((ft_strlen(s1) - \
	(*f_c + *b_c) + 1), sizeof(char)));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	size_t	src_count;
	size_t	f_c;
	size_t	b_c;
	size_t	trim_count;

	if (s1 == NULL || set == NULL)
		return (NULL);
	trim_str = ft_strtrim_malloc_trim_str(&f_c, &b_c, s1, set);
	if (trim_str == NULL)
		return (NULL);
	if (f_c == ft_strlen(s1))
		return (trim_str);
	src_count = 0;
	trim_count = 0;
	while (src_count + f_c < (ft_strlen(s1) - b_c))
	{
		trim_str[trim_count] = s1[src_count + f_c];
		trim_count++;
		src_count++;
	}
	return (trim_str);
}
