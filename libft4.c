/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:14:49 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/03 17:51:54 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*rv;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	rv = (char *) malloc(sizeof(char) * (count * size));
	if (rv == NULL)
		return (NULL);
	ft_bzero(rv, count * size);
	return (rv);
}

int	ft_isalpha(int c)
{
	return (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n_dst;
	size_t	n_src;

	n_src = ft_strlen(src);
	if (dstsize == 0)
		return (n_src);
	n_dst = ft_strlen(dst);
	if (dstsize <= n_dst)
		return (n_src + dstsize);
	ft_strlcpy(dst + n_dst, src, dstsize - n_dst);
	return (n_src + n_dst);
}
