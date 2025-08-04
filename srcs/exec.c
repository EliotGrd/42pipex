/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:49:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/03 21:08:20 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	open_outfile(t_pipex *pppx)
{
	int	flags;
	int	fd;

	if (pppx->mode == HEREDOC)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(pppx->outfile, flags, 0644);
	if (fd == -1)
		fatal_error("outfile openning", errno);
	return (fd);
}

static int	heredoc_input(t_pipex *ppx)
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

static int	open_infile(t_pipex *ppx)
{
	int	fd;

	if (ppx->mode == HEREDOC)
		return (heredoc_input(ppx));
	fd = open(ppx->infile, O_RDONLY);
	if (fd == -1)
		fatal_error(ppx->infile, errno);
	return (fd);
}

static void	child(t_pipex *ppx, size_t i, int prev_fd, int *pipefd)
{
	int	outfile;

	if (dup2(prev_fd, STDIN_FILENO) == -1)
		fatal_error("dup2", errno);
	if (pipefd && dup2(pipefd[1], STDOUT_FILENO) == -1)
		fatal_error("dup2", errno);
	if (!pipefd)
	{
		outfile = open_outfile(ppx);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			fatal_error("dup2", errno);
		close(outfile);
	}
	if (prev_fd != -1)
		close(prev_fd);
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	execve(ppx->cmds[i].path, ppx->cmds[i].argv, ppx->envp);
	fatal_error(ppx->cmds[i].argv[0], errno);
}

void	exec_process(t_pipex *ppx)
{
	size_t	i;
	int		prev_fd;
	int		pipefd[2];
	int		*pipeptr;

	i = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	prev_fd = open_infile(ppx);
	while (i < ppx->cmd_count)
	{
		pipeptr = NULL;
		if (i + 1 < ppx->cmd_count)
		{
			if (pipe(pipefd) == -1)
				fatal_error("pipe", errno);
			pipeptr = pipefd;
		}
		ppx->cmds[i].pid = fork();
		if (ppx->cmds[i].pid == -1)
			fatal_error("fork", errno);
		if (ppx->cmds[i].pid == 0)
			child(ppx, i, prev_fd, pipeptr);
		if (prev_fd != -1)
			close(prev_fd);
		if (pipeptr)
			close(pipeptr[1]);
		if (pipeptr)
			prev_fd = pipeptr[0];
		else
			prev_fd = -1;
		i++;
	}
	while (wait(NULL) > 0)
		;
}
