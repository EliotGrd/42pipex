/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:22:40 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/03 21:07:58 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cmds_info(t_pipex ppx)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	printf("[INFILE] : %s\n", ppx.infile);
	printf("[OUTFILE] : %s\n", ppx.outfile);
	printf("[LIMITER] : %s\n\n", ppx.limiter);
	printf("%zu CMDS | ", ppx.cmd_count);
	while (j < ppx.cmd_count)
	{
		i = 0;
		printf("%zu ARGS\n", ppx.cmds[j].argc);
		while (ppx.cmds[j].argv[i])
		{
			printf("CMD[%zu] | ARG[%zu] : %s\n", j, i, ppx.cmds[j].argv[i]);
			i++;
		}
		printf("PATH:%s\n\n", ppx.cmds[j].path);
		j++;
	}
}

void	print_dirs(t_pipex ppx)
{
	size_t	i;

	i = 0;
	while (ppx.path_dirs[i])
	{
		printf("PATH_ARG[%zu] : %s\n", i, ppx.path_dirs[i]);
		i++;
	}
}

void	ft_free_tab(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		ft_free((void **)&arr[i]);
		i++;
	}
	ft_free((void **)&arr);
}

void	exit_clean(t_pipex *ppx)
{
	size_t	i;

	i = 0;
	ft_free_tab(ppx->path_dirs);
	while (i < ppx->cmd_count)
	{
		ft_free_tab(ppx->cmds[i].argv);
		ft_free((void **)&ppx->cmds[i].path);
		i++;
	}
	ft_free((void **)&ppx->cmds);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.envp = envp;
	ft_bzero((void *)&ppx, sizeof(ppx));
	ppx.path_dirs = fill_path_dirs(envp);
	parse_args(&ppx, ac, av);
	exec_process(&ppx);
	exit_clean(&ppx);
	return (0);
}
