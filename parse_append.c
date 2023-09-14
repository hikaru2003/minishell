/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:30:43 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/20 18:43:27 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokdup(t_token *tok)
{
	char	*word;

	word = ft_strdup(tok->word);
	if (word == NULL)
		fatal_error("strdup");
	return (new_token(word, tok->kind));
}

static void	append_tok(t_token **tok, t_token *elm)
{
	if (*tok == NULL)
	{
		*tok = elm;
		return ;
	}
	append_tok(&(*tok)->next, elm);
}

static void	append_node(t_node **node, t_node *elm)
{
	if (*node == NULL)
	{
		*node = elm;
		return ;
	}
	append_node(&(*node)->next, elm);
}

static bool	is_redirects(t_token *tok)
{
	return (equal_op(tok, ">") || equal_op(tok, "<") \
		|| equal_op(tok, ">>") || equal_op(tok, "<<"));
}

void	append_cmd_elm(t_node *node, t_token **rest, t_token *tok)
{
	if (tok->kind == TK_WORD)
	{
		append_tok(&node->args, tokdup(tok));
		tok = tok->next;
	}
	else if (is_redirects(tok) && tok->next->kind != TK_WORD)
	{
		ft_dprintf(STDERR_FILENO, "%s", ERROR_PREFIX);
		ft_dprintf(2, "syntax error near unexpected token `newline'\n");
		node->node_error = true;
		tok = tok->next;
	}
	else if (equal_op(tok, ">") && tok->next->kind == TK_WORD)
		append_node(&node->redirects, redirect_out(&tok, tok));
	else if (equal_op(tok, ">>") && tok->next->kind == TK_WORD)
		append_node(&node->redirects, redirect_append(&tok, tok));
	else if (equal_op(tok, "<") && tok->next->kind == TK_WORD)
		append_node(&node->redirects, redirect_in(&tok, tok));
	else if (equal_op(tok, "<<") && tok->next->kind == TK_WORD)
		append_node(&node->redirects, redirect_heredoc(&tok, tok));
	*rest = tok;
}
