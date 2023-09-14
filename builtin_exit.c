/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:27:32 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/20 22:08:11 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd)
{
	ft_dprintf(2, "exit\n");
	if (cmd[1] && atoi_check(cmd[1]) == FALSE)
	{
		ft_dprintf(2, "%s", ERROR_PREFIX);
		ft_dprintf(2, "exit: %s: numeric argument required\n", cmd[1]);
		exit(255);
	}
	if (cmd[1] && cmd[2])
	{
		ft_dprintf(2, "%s", ERROR_PREFIX);
		ft_dprintf(2, "exit: too many arguments\n");
		return (1);
	}
	if (cmd[1] && atoi_check(cmd[1]) == TRUE)
		exit(ft_atoi(cmd[1]));
	exit(0);
}
