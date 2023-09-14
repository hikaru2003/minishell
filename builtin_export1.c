/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:18:27 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/20 19:53:15 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_append(t_list *list, t_list *env_head)
{
	t_list	*tmp;
	char	*value_cpy;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp(tmp->key, list->key) == 0)
		{
			value_cpy = ft_strdup(tmp->value);
			if (value_cpy == NULL)
				fatal_error("strdup");
			free(tmp->value);
			tmp->value = ft_strjoin(value_cpy, list->value);
			if (tmp->value == NULL)
				fatal_error("strjoin");
			free(value_cpy);
			free(list->key);
			free(list->value);
			free(list);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	return (FALSE);
}

static void	export_append(char **cmd, t_list *env_head, int i, int len)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		fatal_error("malloc");
	list->sort_flag = 0;
	list->key = ft_substr(cmd[i], 0, len);
	if (!list->key)
		fatal_error("substr");
	if (cmd[i][len + 2] == '\0')
		list->value = ft_strdup("");
	else
		list->value = ft_substr(cmd[i], len + 2, ft_strlen(cmd[i]));
	if (!list->value)
		fatal_error("strdup or substr");
	if (is_append(list, env_head) == FALSE)
		insert(env_head, list);
}

static int	is_new_key(t_list *env_head, t_list *new_list)
{
	t_list	*list;

	list = env_head->next;
	while (list != env_head)
	{
		if (ft_strcmp(list->key, new_list->key) == 0)
		{
			free(list->value);
			list->value = ft_strdup(new_list->value);
			if (list->value == NULL)
				fatal_error("strdup");
			free(new_list->key);
			free(new_list->value);
			free(new_list);
			return (FALSE);
		}
		list = list->next;
	}
	return (TRUE);
}

static void	export_equal(char **cmd, t_list *env_head, int i, int len)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		fatal_error("malloc");
	list->sort_flag = 0;
	list->key = ft_substr(cmd[i], 0, len);
	if (!list->key)
		fatal_error("substr");
	if (cmd[i][len + 1] == '\0')
		list->value = ft_strdup("");
	else
		list->value = ft_substr(cmd[i], len + 1, ft_strlen(cmd[i]));
	if (!list->value)
		fatal_error("strdup or substr");
	if (is_new_key(env_head, list) == TRUE)
		insert(env_head, list);
}

void	do_export(char **cmd, t_list *env_head, int i, int *status)
{
	int	j;

	if (ft_strchr(cmd[i], '=') == NULL)
		*status = non_equal(cmd, env_head, i, 0);
	else
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '+' && cmd[i][j + 1] == '=')
				return (export_append(cmd, env_head, i, j));
			else if (cmd[i][j] == '=')
				return (export_equal(cmd, env_head, i, j));
			else if (is_alpha_num_under(cmd[i][j]))
				j++;
			else
			{
				ft_dprintf(2, "%s", ERROR_PREFIX);
				ft_dprintf(2, "export: `%s': not a valid identifier\n", cmd[i]);
				*status = 1;
				return ;
			}
		}
	}
}
