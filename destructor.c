/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:43:37 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/13 16:02:53 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

t_list	*free_list(t_list *head)
{
	t_list	*list;
	t_list	*tmp;

	list = head->next;
	tmp = list;
	while (list != head)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
	return (NULL);
}

void	free_tok(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->word)
		free(tok->word);
	free_tok(tok->next);
	free(tok);
}

void	free_node(t_node *node)
{
	if (node == NULL)
		return ;
	free_tok(node->args);
	free_tok(node->filename);
	free_tok(node->delim);
	free_node(node->redirects);
	free_node(node->command);
	free_node(node->next);
	free(node);
}
