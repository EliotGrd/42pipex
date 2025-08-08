/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:19:32 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/08 21:38:21 by egiraud          ###   ########.fr       */
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
char		**split_cmd(t_pipex *ppx, char *s);
char		*get_cmd_path(t_pipex *ppx, char *cmd, char **dir);
char		**fill_path_dirs(t_pipex *ppx, char **envp);
char		*ft_strjoin3(t_pipex *ppx, const char *s1, const char *s2,
				const char *s3);

/* EXEC */
void		exec_process(t_pipex *ppx);
int			heredoc_input(t_pipex *ppx);
int			open_infile(t_pipex *ppx);
int			open_outfile(t_pipex *ppx);

/* ERROR */
void		fatal_error(t_pipex *ppx, const char *msg, int err);
void		*pmalloc(t_pipex *ppx, size_t bytes);
void		ft_free(void **ptr);
void		ft_free_tab(char **arr);
void		exit_clean(t_pipex *ppx);
void		cmd_not_found(t_pipex *ppx, int i);

#endif
