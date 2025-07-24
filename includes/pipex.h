/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:19:32 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/24 22:45:02 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	**argv;
	size_t	argc;
}			t_cmd;

typedef enum e_mode
{
	NORMAL,
	HEREDOC
}			t_mode;

typedef struct s_pipex
{
	t_mode	mode;
	char	*infile;
	char	*outfile;
	char	*limiter;
	t_cmd	*cmds;
	size_t	cmd_count;
}			t_pipex;

/* PARSING */
void		parse_args(t_pipex *px, int ac, char **av);

/* ERROR */
void		fatal_error(const char *msg, int err);
void		*pmalloc(size_t bytes);
void		ft_free(void **ptr);

#endif
