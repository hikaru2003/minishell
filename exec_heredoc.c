/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:26:26 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/20 18:07:41 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_list *head, int status)
{
	char	*new_word;
	char	*p;

	p = line;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		fatal_error("calloc");
	while (*p)
	{
		if (is_variable(p))
			expand_variable_str(&new_word, &p, p, head);
		else if (is_special_parameter(p))
			expand_special_prmt_str(&new_word, &p, p, &status);
		else
			append_char(&new_word, *p++);
	}
	free(line);
	return (new_word);
}

static int	check_state_heredoc(void)
{
	if (g_sig == 0)
		;
	else if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

int	read_heredoc(const char *delim, bool is_unqt, t_list *head, int status)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	rl_event_hook = check_state_heredoc;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || g_sig || ft_strcmp(line, delim) == 0)
			break ;
		if (is_unqt)
			line = expand_heredoc_line(line, head, status);
		ft_dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	free(line);
	close(pfd[1]);
	if (g_sig)
	{
		close(pfd[0]);
		g_sig = 0;
		return (-1);
	}
	return (pfd[0]);
}
