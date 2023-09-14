/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token_to_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:42:59 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/13 18:09:43 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_reallocf(char **argv, size_t size)
{
	char	**rv;
	size_t	idx;

	rv = (char **)malloc(sizeof(char *) * size);
	if (rv == NULL)
		return (NULL);
	idx = 0;
	while (argv[idx] != NULL)
	{
		rv[idx] = ft_strdup(argv[idx]);
		if (!rv[idx])
			return (free_array(rv));
		idx++;
	}
	free_array(argv);
	return (rv);
}

static char	**next_token(t_token *tok, int nargs, char **argv)
{
	if (tok == NULL || tok->kind == TK_EOF)
		return (argv);
	argv = ft_reallocf(argv, sizeof(char *) * (nargs + 2));
	if (argv == NULL)
		fatal_error("reallocf");
	argv[nargs] = ft_strdup(tok->word);
	if (argv[nargs] == NULL)
		fatal_error("strdup");
	argv[nargs + 1] = NULL;
	return (next_token(tok->next, nargs + 1, argv));
}

char	**token_list_to_argv(t_token *tok)
{
	char	**argv;

	argv = ft_calloc(1, sizeof(char *));
	if (argv == NULL)
		fatal_error("calloc");
	return (next_token(tok, 0, argv));
}
