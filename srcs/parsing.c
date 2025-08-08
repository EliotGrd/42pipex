/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:23:50 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/08 21:37:35 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	alloc_cmd_array(t_pipex *ppx, size_t n)
{
	size_t	i;

	ppx->cmds = pmalloc(ppx, sizeof(t_cmd) * n);
	ppx->cmd_count = n;
	i = 0;
	while (i < n)
	{
		ppx->cmds[i].argv = NULL;
		ppx->cmds[i].argc = 0;
		i++;
	}
}

static void	fill_commands(t_pipex *ppx, char **av, int first, int last)
{
	size_t	i;
	size_t	j;
	int		cur;

	i = 0;
	cur = first;
	while (cur <= last)
	{
		ppx->cmds[i].argv = split_cmd(ppx, av[cur]);
		if (!ppx->cmds[i].argv || !ppx->cmds[i].argv[0])
			fatal_error(ppx, "empty command", EINVAL);
		ppx->cmds[i].path = get_cmd_path(ppx, ppx->cmds[i].argv[0],
				ppx->path_dirs);
		if (!ppx->cmds[i].path)
			cmd_not_found(ppx, i);
		j = 0;
		while (ppx->cmds[i].argv[j] != NULL)
			j++;
		ppx->cmds[i].argc = j;
		i++;
		cur++;
	}
}

static void	parse_normal(t_pipex *ppx, int ac, char **av)
{
	if (ac < 5)
		fatal_error(ppx, "not enough arguments", EINVAL);
	ppx->mode = NORMAL;
	ppx->infile = av[1];
	ppx->outfile = av[ac - 1];
	ppx->limiter = NULL;
	alloc_cmd_array(ppx, (size_t)(ac - 3));
	fill_commands(ppx, av, 2, ac - 2);
}

static void	parse_heredoc(t_pipex *ppx, int ac, char **av)
{
	if (ac < 6)
		fatal_error(ppx, "not enough arguments", EINVAL);
	ppx->mode = HEREDOC;
	ppx->infile = NULL;
	ppx->limiter = av[2];
	ppx->outfile = av[ac - 1];
	alloc_cmd_array(ppx, (size_t)(ac - 4));
	fill_commands(ppx, av, 3, ac - 2);
}

void	parse_args(t_pipex *ppx, int ac, char **av)
{
	if (ppx == NULL)
		fatal_error(ppx, "parse_args", EINVAL);
	if (ac < 2)
		fatal_error(ppx, "usage", EINVAL);
	if (strcmp(av[1], "here_doc") == 0)
		parse_heredoc(ppx, ac, av);
	else
		parse_normal(ppx, ac, av);
}
