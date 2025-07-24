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
// reuse makefile
// change malloc to calloc but check security of calloc

int	main(int ac, char **av)
{
	t_pipex	ppx;

	ft_bzero(ppx, sizeof(ppx));
	parse_args(&ppx, ac, av);
	// exec
	return (0);
}
