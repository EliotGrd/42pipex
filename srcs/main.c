/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:22:40 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/24 22:58:09 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// update libft_aio with ft_free
// change malloc to calloc but check security of calloc

int	main(int ac, char **av)
{
	int i;
	t_pipex	ppx;
	size_t j = 0;

	ft_bzero((void *)&ppx, sizeof(ppx));
	parse_args(&ppx, ac, av);
	printf("%zu cmds\n", ppx.cmd_count);
	while (j < ppx.cmd_count)
	{
		i = 0;
		while (ppx.cmds[j].argv[i])
		{
			printf("cmd %zu : arg %d : %s\n", j, i, ppx.cmds[j].argv[i]);
			i++;
		}
		j++;
		printf("\n");
	}
	return (0);
}
