/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:49:21 by egiraud           #+#    #+#             */
/*   Updated: 2025/08/05 20:23:47 by egiraud          ###   ########.fr       */
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

/*static void	exec_loop(t_pipex *ppx)
{
	(void)ppx;
}*/

/*void	exec_process(t_pipex *ppx)
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
}*/

/*
static void	exec_loop(t_pipex *ppx, int i, int *pipeptr, int prev_fd)
{

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
		exec_loop(ppx, i, pipeptr, prev_fd);
		i++;
	}
	while (wait(NULL) > 0)
		;
}*/

/* ────────────────────────── helpers ────────────────────────── */

static int	open_first_fd(t_pipex *ppx)
{
	int	fd;

	fd = open_infile(ppx);
	if (fd == -1)
		fatal_error("open", errno);
	return (fd);
}

static int	create_pipe_if_needed(size_t idx, size_t total, int pipefd[2])
{
	if (idx + 1 == total)
		return (0);                /* last command → no pipe */
	if (pipe(pipefd) == -1)
		fatal_error("pipe", errno);
	return (1);
}

static pid_t	spawn_child(t_pipex *ppx,
						  size_t idx,
						  int prev_fd,
						  int *pipeptr)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fatal_error("fork", errno);
	if (pid == 0)                  /* child */
		child(ppx, idx, prev_fd, pipeptr);
	return (pid);                  /* parent keeps PID */
}

static void	close_parent_ends(int *prev_fd, int *pipeptr)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (pipeptr)
		close(pipeptr[1]);        /* close write-end, keep read-end */
}

/* ─────────────────────── public entry ─────────────────────── */

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
		if (create_pipe_if_needed(i, ppx->cmd_count, pipefd))
			pipeptr = pipefd;
		ppx->cmds[i].pid = spawn_child(ppx, i, prev_fd, pipeptr);
		close_parent_ends(&prev_fd, pipeptr);
		if (pipeptr)
			prev_fd = pipeptr[0];  /* read-end becomes next stdin */
		i++;
	}
	while (wait(NULL) > 0)         /* reap them all */
		;
}
