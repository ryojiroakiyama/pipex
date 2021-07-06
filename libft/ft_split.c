/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takataok <takataok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 21:14:31 by takataok          #+#    #+#             */
/*   Updated: 2021/04/11 20:34:36 by takataok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

static int	check(char a, char character)
{
	if (character == a)
		return (0);
	else
		return (1);
}

static char	**set_answer_memo(const char *str, char character)
{
	int	i;
	int	count;

	i = -1;
	count = 1;
	while (str[++i] != '\0')
	{
		if (i != 0)
		{
			if (str[i] == character)
			{
				if (str[i - 1] != character)
				{
					count++;
					continue ;
				}
			}
		}
	}
	if (i == 0 || str[i - 1] == character)
	{
		count--;
	}
	return ((char **)malloc((count + 1) * (sizeof(char *))));
}

static int	ft_split_str(char **answer, const char *str, char character)
{
	int		i;
	int		j;
	int		head;

	i = -1;
	j = -1;
	head = 0;
	while (++i <= (int)ft_strlen(str))
	{
		if (check(str[i], character) == 0 || str[i] == '\0')
		{
			if (head == i)
				head++;
			else
			{
				answer[++j] = (char *)malloc(sizeof(char) * (i - head + 1));
				if (answer[j] == NULL)
					return (-2);
				ft_strlcpy(answer[j], &str[head], i - head + 1);
				answer[j + 1] = NULL;
				head = i + 1;
			}
		}
	}
	return (j);
}

char	**ft_split(const char *str, char character)
{
	char	**answer;
	int		count;

	if (str == NULL)
		return (NULL);
	answer = set_answer_memo(str, character);
	if (answer == NULL)
		return (NULL);
	count = ft_split_str(answer, str, character);
	if (count == -2)
	{
		count = -1;
		while (answer[++count] != NULL)
			free(answer[count]);
		free(answer);
		return (NULL);
	}
	else if (count == -1)
		answer[count + 1] = NULL;
	return (answer);
}
