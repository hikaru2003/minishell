/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:59 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/18 19:09:36 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	word_single_quote(char **rest, char *line, t_token *tok_head)
{
	line++;
	while (*line != SINGLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
	{
		tokenize_error("Unclosed single quote", &line, line, tok_head);
		return (false);
	}
	else
		line++;
	*rest = line;
	return (true);
}

static bool	word_double_quote(char **rest, char *line, t_token *tok_head)
{
	line++;
	while (*line != DOUBLE_QUOTE_CHAR)
		line++;
	if (*line == '\0')
	{
		tokenize_error("Unclosed double quote", &line, line, tok_head);
		return (false);
	}
	else
		line++;
	*rest = line;
	return (true);
}

static char	*ft_strndup(const char *s, size_t len)
{
	char	*rv;
	size_t	idx;

	rv = (char *)malloc(sizeof(char) * (len + 1));
	if (!rv)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		rv[idx] = s[idx];
		idx++;
	}
	rv[len] = '\0';
	return (rv);
}

t_token	*word(char **rest, char *line, t_token *tok_head)
{
	const char	*start = line;
	char		*word;

	while (*line && !is_metacharacter(*line))
	{
		if (*line == SINGLE_QUOTE_CHAR)
		{
			if (word_single_quote(&line, line, tok_head) == false)
				break ;
		}
		else if (*line == DOUBLE_QUOTE_CHAR)
		{
			if (word_double_quote(&line, line, tok_head) == false)
				break ;
		}
		else
			line++;
	}
	word = ft_strndup(start, (size_t)(line - start));
	if (word == NULL)
		fatal_error("strndup");
	*rest = line;
	return (new_token(word, TK_WORD));
}
