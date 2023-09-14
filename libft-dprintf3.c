/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft-dprintf3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:17:05 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/03 18:29:37 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_put_c(int fd, t_args *args, char c, int res)
{
	while (args->flag != '0' && args->spec == 0 && args->width-- > 1)
		res += ft_putchar_int(fd, ' ');
	while (args->flag == '0' && args->width-- > 1)
		res += ft_putchar_int(fd, '0');
	if (args->spec == 0)
		return (res);
	while (args->flag != '-' && args->width-- > 1)
		res += ft_putchar_int(fd, ' ');
	res += ft_putchar_int(fd, c);
	while (args->flag == '-' && args->width-- > 1)
		res += ft_putchar_int(fd, ' ');
	return (res);
}

static int	ft_putstrl(int fd, char *str, int len)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i] && i < len)
		res += ft_putchar_int(fd, str[i++]);
	return (res);
}

int	ft_put_s(int fd, t_args *args, char *s, int res)
{
	int		putlen;
	size_t	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (len > INT_MAX)
		return (-1);
	putlen = len;
	if (args->has_prec && putlen > args->prec)
		putlen = args->prec;
	while (args->flag != '-' && args->flag != '0' && args->width-- > putlen)
		res += ft_putchar_int(fd, ' ');
	while (args->flag == '0' && args->width-- > putlen)
		res += ft_putchar_int(fd, '0');
	res += ft_putstrl(fd, s, putlen);
	while (args->flag == '-' && args->width-- > putlen)
		res += ft_putchar_int(fd, ' ');
	return (res);
}
