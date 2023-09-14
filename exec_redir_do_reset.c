/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_do_reset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:26:26 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/22 15:37:35 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_redirect(t_node *node)
{
	if (node->kind == ND_REDIR_OUT)
		return (true);
	else if (node->kind == ND_REDIR_IN)
		return (true);
	else if (node->kind == ND_REDIR_APPEND)
		return (true);
	else if (node->kind == ND_REDIR_HEREDOC)
		return (true);
	else
		return (false);
}

static int	change_fd(int fd)
{
	int	newfd;

	newfd = dup(fd);
	if (newfd == -1)
		fatal_error("dup");
	if (close(fd) < 0)
		fatal_error("close");
	return (newfd);
}

void	do_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	if (is_redirect(redir))
	{
		redir->new_targetfd = change_fd(redir->targetfd);
		dup2(redir->filefd, redir->targetfd);
	}
	else
		assert_error("do_redirect");
	do_redirect(redir->next);
}

void	reset_redirect(t_node *redir)
{
	if (redir == NULL)
		return ;
	reset_redirect(redir->next);
	if (is_redirect(redir))
	{
		close(redir->filefd);
		close(redir->targetfd);
		dup2(redir->new_targetfd, redir->targetfd);
	}
	else
		assert_error("reset_redirect");
}
