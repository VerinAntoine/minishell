/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averin <averin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:26:42 by averin            #+#    #+#             */
/*   Updated: 2024/01/16 09:40:25 by averin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/**
 * Close all opened fds
 * @param exec current exec status
*/
static void	close_fds(t_exec *exec)
{
	if (exec->infile != -1)
		(close(exec->infile), exec->infile = -1);
	if (exec->outfile != -1)
		(close(exec->outfile), exec->outfile = -1);
	if (exec->pipes[0] != -1)
		(close(exec->pipes[0]), exec->pipes[0] = -1);
	if (exec->pipes[1] != -1)
		(close(exec->pipes[1]), exec->pipes[1] = -1);
}

static int	duplicate_fds(int infd, int outfd)
{
	if (infd == -1)
		infd = 0;
	if (outfd == -1)
		outfd = 1;
	return (dup2(infd, STDIN_FILENO) == -1
		|| dup2(outfd, STDOUT_FILENO) == -1);
}

/**
 * Execute the command with the args and the env, redirect input and output
 * @param exec executable path
 * @param args commands' args
 * @param envp envp
 * @param fds fd to redirect to {in, out}
 * @return execution's pid or -1
*/
int	do_exec(char *exec, char **args, char **envp, int *fds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1
			|| dup2(fds[1], STDOUT_FILENO) == -1)
			(perror("redirect error"), exit(254));
		(close(fds[0]), close(fds[1]));
		if (execve(exec, args, envp) == -1)
			(perror("execution error"), exit(253));
	}
	return (pid);
}
