/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:53:26 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/22 14:20:25 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

void	expand_special_prmt_str(char **dst, char **rest, char *p, int *status)
{
	unsigned int	num;

	if (!is_special_parameter(p))
		assert_error("Expected special parameter");
	p += 2;
	num = *status;
	append_num(dst, num);
	*rest = p;
}

void	expand_variable_str(char **dst, char **rest, char *p, t_list *head)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	if (*p != '$')
		assert_error("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		assert_error("Variable must starts with alphabet or underscore");
	append_char(&name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++);
	value = ft_getenv(head, name);
	free(name);
	name = value;
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
	free(name);
}

static void	expand_variable_tok(t_token *tok, t_list *head, int *status)
{
	char	*new_word;
	char	*p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			p = append_single_quote(&new_word, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			p = append_double_quote(&new_word, p, head, status);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p, head);
		else if (is_special_parameter(p))
			expand_special_prmt_str(&new_word, &p, p, status);
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	expand_variable_tok(tok->next, head, status);
}

void	expand_variable(t_node *node, t_list *head, int *status)
{
	if (node == NULL)
		return ;
	expand_variable_tok(node->args, head, status);
	expand_variable_tok(node->filename, head, status);
	expand_variable(node->redirects, head, status);
	expand_variable(node->command, head, status);
	expand_variable(node->next, head, status);
}
