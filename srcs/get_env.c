/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:58:58 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/31 21:17:37 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**fill_path_dirs(char **envp)
{
	char	**dirs;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!*path || !path)
	{
		dirs = pmalloc(sizeof(char *) * 1);
		dirs[0] = NULL;
	}
	dirs = ft_split(path, ':');
	if (!dirs)
		fatal_error("malloc", EINVAL);
	return (dirs);
}

char	*get_cmd_path(char *cmd, char **dirs)
{
	int		i;
	char	*to_test;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	i = -1;
	while (dirs[++i])
	{
		to_test = ft_strjoin3(dirs[i], "/", cmd);
		if (access(to_test, X_OK) == 0)
			return (to_test);
		free(to_test);
	}
	return (NULL);
}
