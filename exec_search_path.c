/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_search_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snemoto <snemoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:01:19 by snemoto           #+#    #+#             */
/*   Updated: 2023/08/12 13:54:57 by snemoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_path(const char *path)
{
	char	*dup;

	if (access(path, X_OK) == 0)
	{	
		dup = ft_strdup(path);
		if (dup == NULL)
			fatal_error("strdup");
		return (dup);
	}
	return (NULL);
}

char	*ft_getenv(t_list *head, char *name)
{
	t_list	*list;

	list = head->next;
	while (list != head)
	{
		if (ft_strcmp(list->key, name) == 0)
			return (ft_strdup(list->value));
		list = list->next;
	}
	return (NULL);
}

char	*search_path(const char *filename, t_list *head)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_getenv(head, "PATH");
	while (value != NULL && *value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			ft_strlcpy(path, value, end - value + 1);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		dup = check_path(path);
		if (dup != NULL)
			return (dup);
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}
