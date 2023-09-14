/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft-dprintf2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:17:05 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/03 18:52:18 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_digits_base(unsigned int ud, int c)
{
	int	digits;
	int	base;

	base = 10;
	if (c == 'x' || c == 'X')
		base = 16;
	digits = 0;
	while (ud / base)
	{
		digits++;
		ud /= base;
	}
	digits++;
	return (digits);
}

static int	ft_put_unbr(int fd, unsigned int ud, int res)
{
	if (ud / 10)
		res = ft_put_unbr(fd, ud / 10, res);
	res += ft_putchar_int(fd, (ud % 10) + '0');
	return (res);
}

static int	ft_putd(int fd, t_args *args, int d, int res)
{
	if (d < 0)
		res += ft_putchar_int(fd, '-');
	while (args->has_prec == 0 && args->flag == '0')
		res += ft_putchar_int(fd, '0');
	if (0 <= d && (args->flag == ' ' || args->flag == '+'))
		res += ft_putchar_int(fd, args->flag);
	while (args->pad-- > 0)
		res += ft_putchar_int(fd, '0');
	if (d < 0)
		res = ft_put_unbr(fd, -d, res);
	else
		res = ft_put_unbr(fd, d, res);
	return (res);
}

int	ft_put_d(int fd, t_args *args, int d, int res)
{
	int	len;
	int	putlen;

	len = ft_get_digits_base(d, 10);
	if (d < 0)
		len = ft_get_digits_base(-d, 10);
	if (args->has_prec && args->prec == 0 && d == 0)
		len = 0;
	if (args->prec > len)
		args->pad = args->prec - len;
	if (d < 0)
		len++;
	putlen = len + args->pad;
	if (args->flag == 0 || (args->flag == '0' && args->has_prec) \
		|| (args->flag == '-' && args->has_prec && args->prec == 0 && d == 0))
		while (args->width-- > putlen)
			res += ft_putchar_int(fd, ' ');
	if (args->has_prec && args->prec == 0 && d == 0)
		return (res);
	res = ft_putd(fd, args, d, res);
	while (args->flag == '-' && args->width-- > putlen)
		res += ft_putchar_int(fd, ' ');
	return (res);
}
