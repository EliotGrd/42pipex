/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:19:32 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/05 19:24:50 by egiraud          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char	**path_dirs;
	char	**envp;
	size_t	cmd_count;
}			t_pipex;

/* PARSING */
void		parse_args(t_pipex *ppx, int ac, char **av);
char		**split_cmd(char *s);
char		*get_cmd_path(char *cmd, char **dir);
char		**fill_path_dirs(char **envp);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);

/* EXEC */
void		exec_process(t_pipex *ppx);
int			heredoc_input(t_pipex *ppx);

/* ERROR */
void		fatal_error(const char *msg, int err);
void		*pmalloc(size_t bytes);
void		ft_free(void **ptr);
void		ft_free_tab(char **arr);

#endif
