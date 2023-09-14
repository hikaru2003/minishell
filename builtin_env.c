/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:28:54 by hikaru            #+#    #+#             */
/*   Updated: 2023/08/15 17:48:37 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_list *env_head, t_node *node)
{
	t_list	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (ft_strcmp(tmp->value, "\0"))
			ft_dprintf(node->outpipe[1], "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
