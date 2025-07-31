/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:19:32 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/29 22:50:57 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum s_state
{
	S_OW,
	S_IW,
	S_INQUOTE
}			t_state;

typedef struct s_cmd
{
	char	**argv;
	pid_t	pid;
	char	*path;
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
char		**split_cmd(char *s);

/* ERROR */
void		fatal_error(const char *msg, int err);
void		*pmalloc(size_t bytes);
void		ft_free(void **ptr);

#endif
