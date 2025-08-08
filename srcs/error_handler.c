/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:35:02 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/08 21:38:26 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fatal_error(t_pipex *ppx, const char *msg, int err)
{
	errno = err;
	perror(msg);
	exit_clean(ppx);
	exit(err);
}

void	*pmalloc(t_pipex *ppx, size_t bytes)
{
	void	*p;

	p = ft_calloc(bytes, 1);
	if (p == NULL)
		fatal_error(ppx, "malloc", ENOMEM);
	return (p);
}

void	cmd_not_found(t_pipex *ppx, int i)
{
	ft_putstr_fd(ppx->cmds[i].argv[0], 2);
	ft_putendl_fd(": Command not found", 2);
	exit_clean(ppx);
	exit(ENOENT);
}
