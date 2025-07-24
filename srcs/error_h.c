/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_h.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:29:04 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/24 22:45:09 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free(void **ptr)
{
	if (!*ptr || !ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	fatal_error(const char *msg, int err)
{
	errno = err;
	perror(msg);
	exit(err);
}

void	*pmalloc(size_t bytes)
{
	void	*p;

	p = malloc(bytes);
	if (p == NULL)
		fatal_error("malloc", ENOMEM);
	return (p);
}
