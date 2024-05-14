/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:02:21 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 21:41:02 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void fds_redirection(int fds[2], t_elem var, char flag)
{
	if (flag == 'f')
	{
		var.infile_fd = check_file(var.infile, 'i');
		if (!var.infile_fd)
		{
			close_fd((int[4]){var.in_fd, var.ofile_fd, -1}, var.path, 0);
			close_fd((int[4]){fds[0], fds[1], -1}, NULL, 1);
		}
		dup2(var.infile_fd, 0);
		dup2(fds[1], 1);
		close_fd((int[4]){fds[0], fds[1], var.infile_fd, -1}, NULL, 0);
		close_fd((int [4]){var.in_fd, var.ofile_fd}, NULL, 0);
	}
	else if (flag == 'l')
	{
		dup2(var.ofile_fd, 1);
		close_fd((int[4]){fds[1], fds[0], var.ofile_fd, -1}, NULL, 0);
		close(var.in_fd); 
	}
	else
	{
		dup2(fds[1], 1);
		close_fd((int[4]){fds[0], fds[1], -1}, NULL, 0);
		close_fd((int [4]){var.ofile_fd, var.in_fd, -1}, NULL, 0);
	}
}

void ft_child(int fds[2], t_elem var, char *arg, char flag)
{
	char *path;
	char **cmd_arg;

	path = NULL;
	fds_redirection(fds, var, flag);
	cmd_arg = parce_cmd(var, arg, &path);
	if (!cmd_arg)
	{
		close(var.in_fd);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, var.path, 1);
	}
	if (execve(path, cmd_arg, NULL) == -1)
	{
		free(path);
		print_exec_err(strerror(errno), cmd_arg[0]);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, cmd_arg, 0);
		close_fd((int[4]){var.in_fd, -1}, var.path, 1);
	}
}

void execute_cmd(t_elem var, char *arg, char flag)
{
	int fds[2];

	if (pipe(fds) == -1)
	{
		perror("pipe");
		dup2(var.in_fd, 0);
		close_fd((int[4]){var.in_fd, var.ofile_fd, -1}, var.path, 1);
	}
	var.id = fork();
	if (var.id == -1)
	{
		perror("fork");
		dup2(var.in_fd, 0);
		close_fd((int [4]){fds[0], fds[1], -1}, var.path, 0);
		close_fd((int[4]){var.in_fd, var.ofile_fd, -1}, NULL, 1);
	}
	else if (var.id == 0)
		ft_child(fds, var, arg, flag);
	if (dup2(fds[0], 0) == -1)
		perror("dup2");
	close_fd((int[4]){fds[1], fds[0], -1}, NULL, 0);
}
