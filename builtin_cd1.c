/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:20:41 by hmorisak          #+#    #+#             */
/*   Updated: 2023/08/20 22:23:19 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(char **cmd, DIR *dir)
{
	struct dirent	*dp;

	dp = readdir(dir);
	while (dp != NULL)
	{
		if (ft_strcmp(cmd[1], dp->d_name) == 0)
		{
			ft_dprintf(2, "%s", ERROR_PREFIX);
			ft_dprintf(2, "cd: %s: Not a directory\n", cmd[1]);
			break ;
		}
		dp = readdir(dir);
	}
	if (!dp)
	{
		ft_dprintf(2, "%s", ERROR_PREFIX);
		ft_dprintf(2, "cd: %s: No such file or directory\n", cmd[1]);
	}
	free(dir->__dd_buf);
	free(dir);
}
