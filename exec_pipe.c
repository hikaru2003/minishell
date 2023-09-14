/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/22 14:42:55 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_pipeline(pid_t last_pid, int status)
{
	pid_t	wait_result;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
		{
			if (WIFSIGNALED(wstatus))
				status = 128 + WTERMSIG(wstatus);
			else
				status = WEXITSTATUS(wstatus);
		}
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
			else if (errno == EINTR)
				continue ;
			else
				fatal_error("wait");
		}
	}
	return (status);
}

static char	**list_to_array(t_list *env_head)
{
	int		i;
	t_list	*tmp;
	char	**array;

	i = 0;
	tmp = env_head->next;
	array = (char **)malloc(sizeof(char *) * (env_head->count + 1));
	if (!array)
		return (NULL);
	while (i < env_head->count && tmp != env_head)
	{
		if (tmp->value)
			array[i] = ft_strdup(tmp->value);
		if (!array[i])
			return (free_array(array));
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

static void	exec_child(char **argv, t_list *head, t_node *node)
{
	char	*path;
	char	**array;

	path = argv[0];
	if (path == NULL)
		return ;
	reset_sig(SIGQUIT);
	reset_sig(SIGINT);
	prepare_pipe_child(node);
	do_redirect(node->command->redirects);
	if (ft_strchr(path, '/') == NULL)
		path = search_path(path, head);
	if (path == NULL || access(path, F_OK) < 0)
		err_exit(argv[0], "command not found", 127);
	array = list_to_array(head);
	if (!array)
		fatal_error("malloc");
	execve(path, argv, array);
	free_array(array);
	reset_redirect(node->command->redirects);
	fatal_error("execve");
}

static pid_t	exec_pipeline(t_node *node, t_list *head, int status)
{
	pid_t	pid;
	char	**argv;

	prepare_pipe(node);
	argv = token_list_to_argv(node->command->args);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		if (is_builtin(argv) != TRUE)
			exec_child(argv, head, node);
		else
			exit(built_in_cmd(argv, head, node, status));
	}
	free_array(argv);
	close_pipe(node);
	if (node->next)
		return (exec_pipeline(node->next, head, status));
	return (pid);
}

int	expand_and_exec(t_node *node, t_list *head, int *last_status)
{
	int		status;
	char	**argv;

	status = *last_status;
	expand_variable(node, head, &status);
	expand_quote_removal(node);
	if (open_redir_file(node, head, status) < 0)
		return (ERRPR_OPEN_REDIR);
	argv = token_list_to_argv(node->command->args);
	if (is_builtin(argv) == TRUE && !node->next)
	{
		do_redirect(node->command->redirects);
		status = built_in_cmd(argv, head, node, status);
		reset_redirect(node->command->redirects);
	}
	else
		status = wait_pipeline(exec_pipeline(node, head, status), status);
	free_array(argv);
	return (status);
}
