/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:49:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/08 21:36:12 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	child(t_pipex *ppx, size_t i, int prev_fd, int *pipefd)
{
	int	outfile;

	if (dup2(prev_fd, STDIN_FILENO) == -1)
		fatal_error(ppx, "dup2", errno);
	if (pipefd && dup2(pipefd[1], STDOUT_FILENO) == -1)
		fatal_error(ppx, "dup2", errno);
	if (!pipefd)
	{
		outfile = open_outfile(ppx);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			fatal_error(ppx, "dup2", errno);
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
	fatal_error(ppx, ppx->cmds[i].path, errno);
}

static int	create_pipe_if_needed(t_pipex *ppx, size_t idx, size_t total,
		int pipefd[2])
{
	if (idx + 1 == total)
		return (0);
	if (pipe(pipefd) == -1)
		fatal_error(ppx, "pipe", errno);
	return (1);
}

static pid_t	spawn_child(t_pipex *ppx, size_t idx, int prev_fd, int *pipeptr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fatal_error(ppx, "fork", errno);
	if (pid == 0)
		child(ppx, idx, prev_fd, pipeptr);
	return (pid);
}

static void	close_parent_ends(int *prev_fd, int *pipeptr)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (pipeptr)
		close(pipeptr[1]);
}

void	exec_process(t_pipex *ppx)
{
	size_t	i;
	int		prev_fd;
	int		pipefd[2];
	int		*pipeptr;

	i = 0;
	prev_fd = open_infile(ppx);
	while (i < ppx->cmd_count)
	{
		pipeptr = NULL;
		if (create_pipe_if_needed(ppx, i, ppx->cmd_count, pipefd))
			pipeptr = pipefd;
		ppx->cmds[i].pid = spawn_child(ppx, i, prev_fd, pipeptr);
		close_parent_ends(&prev_fd, pipeptr);
		if (pipeptr)
			prev_fd = pipeptr[0];
		i++;
	}
	while (wait(NULL) > 0)
		;
}
