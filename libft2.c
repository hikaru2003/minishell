/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 16:09:06 by hmorisak          #+#    #+#             */
/*   Updated: 2023/08/11 18:42:31 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	char	*rtn;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	rtn = tmp;
	while (*s1 != '\0')
	{
		*tmp = *s1;
		tmp++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*tmp = *s2;
		tmp++;
		s2++;
	}
	*tmp = '\0';
	return (rtn);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	slen;
	size_t	i;

	if (s)
	{
		slen = ft_strlen(s);
		i = 0;
		while (i < slen)
		{
			write(fd, &s[i], sizeof(char));
			i++;
		}
	}
}

static int	check_flow(long sum, char c, int flag)
{
	if (LONG_MAX / 10 < sum && c && flag == 0)
		return (1);
	if (sum == LONG_MAX / 10 && LONG_MAX % 10 < c - '0' && flag == 0)
		return (1);
	if (LONG_MIN / 10 > -sum && c && flag == 1)
		return (-1);
	if (LONG_MIN / 10 == -sum && LONG_MIN % 10 > -(c - '0') && flag == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		flag;
	long	sum;

	flag = 0;
	sum = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = 1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		sum = sum * 10 + (*str - '0');
		str++;
		if (check_flow(sum, *str, flag) > 0)
			return ((int)LONG_MAX);
		if (check_flow(sum, *str, flag) < 0)
			return ((int)LONG_MIN);
	}
	if (flag == 1)
		sum *= -1;
	return ((int)sum);
}

int	atoi_check(const char *str)
{
	if (*str == '\0')
		return (FALSE);
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
		str++;
	if (*str != '\0')
		return (FALSE);
	return (TRUE);
}
