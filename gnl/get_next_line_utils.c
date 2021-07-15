#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

ssize_t	ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;
	ssize_t	i;

	str = (char *)s;
	ch = (char)c;
	i = 0;
	while (1)
	{
		if (str[i] == ch)
			return (i);
		if (!str[i])
			break ;
		i++;
	}
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

char	*ft_subnstr(char const *s, unsigned int start, size_t len)
{
	char	*ans;

	if (!s)
		return (NULL);
	if (!len)
	{
		ans = (char *)malloc(sizeof(char) * 1);
		if (!ans)
			return (NULL);
		ans[0] = '\0';
		return (ans);
	}
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s + start, len + 1);
	return (ans);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t s2_len)
{
	char	*dst;
	size_t	len;
	size_t	s1_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen((char *)s1);
	len = s1_len + s2_len;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcpy(dst + s1_len, s2, s2_len + 1);
	return (dst);
}
