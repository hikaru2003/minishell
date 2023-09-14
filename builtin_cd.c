/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorisak <hmorisak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:26:04 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/20 22:25:07 by hmorisak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(char *oldpwd, t_list *env_head)
{
	t_list	*tmp;
	char	*old;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp("OLDPWD", tmp->key) == 0)
		{
			old = tmp->value;
			tmp->value = ft_strdup(oldpwd);
			if (tmp->value == NULL)
				fatal_error("strdup");
			free(old);
			break ;
		}
		tmp = tmp->next;
	}
}

static void	update_pwd(char *cwd, t_list *env_head)
{
	t_list	*tmp;
	char	*old;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp("PWD", tmp->key) == 0)
		{
			old = tmp->value;
			if (getcwd(cwd, 512) != NULL)
				tmp->value = ft_strdup(getcwd(cwd, 512));
			if (tmp->value == NULL)
				fatal_error("strdup");
			free(old);
			break ;
		}
		tmp = tmp->next;
	}
}

static char	*find_home_dir(t_list *env_head)
{
	t_list	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("/Users");
}

static char	*find_pwd(t_list *env_head)
{
	t_list	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (find_home_dir(env_head));
}

int	ft_cd(char **cmd, char *cwd, t_list *env_head)
{
	DIR		*dir;
	char	*oldpwd;

	oldpwd = find_pwd(env_head);
	if (getcwd(cwd, 512) != NULL)
		oldpwd = getcwd(cwd, 512);
	if (!cmd[1])
		chdir(find_home_dir(env_head));
	else if (chdir(cmd[1]) == -1)
	{
		dir = opendir(oldpwd);
		if (dir == NULL)
		{
			ft_dprintf(2, "%s", ERROR_PREFIX);
			ft_dprintf(2, "cd: %s: No such file or directory\n", cmd[1]);
		}
		else
			ft_chdir(cmd, dir);
		return (1);
	}
	update_oldpwd(oldpwd, env_head);
	update_pwd(cwd, env_head);
	return (0);
}
