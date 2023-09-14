/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:14:49 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/07 07:13:08 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*find_min(t_list *env_head, t_list *sort, t_list *min)
{
	while (sort != env_head)
	{
		if (sort->sort_flag == 0 && ft_strcmp(min->key, sort->key) > 0)
			min = sort;
		sort = sort->next;
	}
	return (min);
}

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)buf;
	while (n--)
	{
		*tmp = (unsigned char)ch;
		tmp++;
	}
	return (buf);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*c1 != '\0' || *c2 != '\0')
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp1 = s1;
	const unsigned char	*tmp2 = s2;

	while (n-- > 0)
	{
		if (*tmp1 != *tmp2)
			return (*tmp1 - *tmp2);
		tmp1++;
		tmp2++;
	}
	return (0);
}
