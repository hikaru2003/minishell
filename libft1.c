/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:21:43 by hmorisak          #+#    #+#             */
/*   Updated: 2023/05/07 22:44:30 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n-- && (*c1 != '\0' || *c2 != '\0'))
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*substring;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < (size_t)start)
		return (ft_strdup(""));
	if (len > slen)
		len = slen;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	slen;
	int		i;

	slen = ft_strlen((char *)s1);
	tmp = (char *)malloc(sizeof(char) * (slen + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (dstsize == 0)
		return (len);
	if (dstsize > 0)
	{
		while (dstsize-- != 1 && *src != '\0')
		{
			*dst = *src;
			dst++;
			src++;
		}
		*dst = '\0';
	}
	return (len);
}

size_t	ft_strlen(const char *c)
{
	size_t	len;

	len = 0;
	while (*c != '\0')
	{
		len++;
		c++;
	}
	return (len);
}
