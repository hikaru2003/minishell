/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_open.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:26:26 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/24 16:24:28 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_redir_file(t_node *node, t_list *head, int status)
{
	if (node->kind == ND_REDIR_OUT)
		node->filefd = open(node->filename->word,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (node->kind == ND_REDIR_APPEND)
		node->filefd = open(node->filename->word,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (node->kind == ND_REDIR_IN)
		node->filefd = open(node->filename->word,
				O_RDONLY);
	else if (node->kind == ND_REDIR_HEREDOC)
	{
		node->filefd = read_heredoc(node->delim->word,
				node->is_delim_unquote, head, status);
		if (isatty(STDIN_FILENO))
			rl_event_hook = check_state;
	}
	else
		assert_error("open_redir_file");
}

int	open_redir_file(t_node *node, t_list *head, int status)
{
	if (node == NULL)
		return (0);
	if (node->kind == ND_PIPELINE)
	{
		if (open_redir_file(node->command, head, status) < 0)
			return (-1);
		if (open_redir_file(node->next, head, status) < 0)
			return (-1);
		return (0);
	}
	else if (node->kind == ND_SIMPLE_CMD)
		return (open_redir_file(node->redirects, head, status));
	else
		check_redir_file(node, head, status);
	if (node->filefd < 0)
	{
		if (node->kind == ND_REDIR_OUT
			|| node->kind == ND_REDIR_APPEND
			|| node->kind == ND_REDIR_IN)
			xperror(node->filename->word);
		return (-1);
	}
	return (open_redir_file(node->next, head, status));
}
