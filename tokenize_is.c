/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:59 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/16 18:09:16 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

bool	is_word(const char *s)
{
	return (*s && !is_metacharacter(*s));
}

bool	is_eof(t_token *tok)
{
	return (tok->kind == TK_EOF);
}

bool	check_op(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, ft_strlen(keyword)) == 0);
}
