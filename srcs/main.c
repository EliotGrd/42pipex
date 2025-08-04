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
	size_t i;
	size_t j;

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
		printf("PATH:%s\n\n",ppx.cmds[j].path);
		j++;
	}
}

void	print_dirs(t_pipex ppx)
{
	size_t i;

	i = 0;
	while (ppx.path_dirs[i])
	{
		printf("PATH_ARG[%zu] : %s\n", i, ppx.path_dirs[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	ppx;

	ppx.envp = envp;
	ft_bzero((void *)&ppx, sizeof(ppx));
	ppx.path_dirs = fill_path_dirs(envp);
	parse_args(&ppx, ac, av);
	exec_process(&ppx);

	/* DEBUG */
	cmds_info(ppx);
	//print_dirs(ppx);
	return (0);
}
