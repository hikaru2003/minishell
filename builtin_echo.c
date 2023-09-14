/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikaru <hikaru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:24:57 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/19 16:30:00 by hikaru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_option(char **cmd, int *i)
{
	int		j;

	j = 2;
	while (cmd[*i] && cmd[*i][0] == '-' && cmd[*i][1] == 'n')
	{
		j = 2;
		while (cmd[*i][j] && cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j])
			break ;
		(*i)++;
	}
	if (*i == 1)
		return (FALSE);
	return (TRUE);
}

int	ft_echo(char **cmd, t_node *node)
{
	int		i;
	bool	flag;

	i = 1;
	if (!cmd[i])
	{
		ft_dprintf(node->outpipe[1], "\n");
		return (0);
	}
	flag = is_option(cmd, &i);
	while (cmd[i])
	{
		ft_dprintf(node->outpipe[1], "%s", cmd[i]);
		if (cmd[++i])
			ft_dprintf(node->outpipe[1], " ");
	}
	if (flag == FALSE)
		ft_dprintf(node->outpipe[1], "\n");
	return (0);
}
