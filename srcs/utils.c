/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:58:29 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/05 19:25:47 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	char	*p;

	result = pmalloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	p = result;
	if (s1)
	{
		ft_memcpy(p, s1, ft_strlen(s1));
		p += ft_strlen(s1);
	}
	if (s2)
	{
		ft_memcpy(p, s2, ft_strlen(s2));
		p += ft_strlen(s2);
	}
	if (s3)
	{
		ft_memcpy(p, s3, ft_strlen(s3));
		p += ft_strlen(s3);
	}
	*p = 0;
	return (result);
}

int	heredoc_input(t_pipex *ppx)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		fatal_error("pipe", errno);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, ppx->limiter, ft_strlen(ppx->limiter))
			&& line[ft_strlen(ppx->limiter)] == '\n')
		{
			ft_free((void **)&line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		ft_free((void **)&line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	open_outfile(t_pipex *ppx)
{
	int	flags;
	int	fd;

	if (ppx->mode == HEREDOC)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(ppx->outfile, flags, 0644);
	if (fd == -1)
		fatal_error("outfile openning", errno);
	return (fd);
}

int	open_infile(t_pipex *ppx)
{
	int	fd;

	if (ppx->mode == HEREDOC)
		return (heredoc_input(ppx));
	fd = open(ppx->infile, O_RDONLY);
	if (fd == -1)
		fatal_error(ppx->infile, errno);
	return (fd);
}
