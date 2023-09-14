/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:49:52 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/24 16:33:13 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

static void	setup_signal(void)
{
	extern int	_rl_echo_control_chars;

	g_sig = 0;
	_rl_echo_control_chars = 0;
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
	ignore_sig(SIGQUIT);
	setup_sig(SIGINT);
}

static t_list	*env_to_list(char **environ)
{
	t_list	*head;
	int		i;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		fatal_error("malloc");
	head->count = 0;
	head->next = head;
	head->prev = head;
	i = 0;
	while (environ[i])
		if (make_list(head, i++) == NULL)
			return (NULL);
	return (head);
}

static bool	check_error(t_node *node)
{
	if (node->command->node_error)
		return (true);
	if (node->next)
		return (check_error(node->next));
	return (false);
}

static void	handle_line(char *line, int *status, t_list *head)
{
	t_token	*tok;
	t_token	*tok_head;
	t_node	*node;

	tok = tokenize(line);
	tok_head = tok;
	free(line);
	if (is_eof(tok))
		;
	else if (tok_head->tok_error)
		*status = ERROR_TOKENIZE;
	else
	{
		node = parse(&tok, tok, head);
		if (check_error(node))
			*status = ERROR_PARSE;
		else
			*status = expand_and_exec(node, head, status);
		free_node(node);
	}
	free_tok(tok_head);
}

int	main(void)
{
	char		*line;
	t_list		*head;
	static int	status;

	status = 0;
	setup_signal();
	head = env_to_list(environ);
	if (head == NULL)
		fatal_error("malloc");
	while (1)
	{
		if (g_sig == SIGINT)
			line = readline("\n");
		else
			line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		handle_line(line, &status, head);
	}
	free_list(head);
	exit(status);
}
