/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:56:18 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 20:10:53 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void fds_redirection(int fds[2], t_elem var, char flag)
{
	if (flag == 'h')
	{
		dup2(var.end[0], 0);
		dup2(fds[1], 1);
		close_fd((int[4]){var.end[0], var.end[1], fds[0], -1}, NULL, 0);
		close_fd((int[4]){fds[1], var.ofile_fd, var.in_fd, -1}, NULL, 0);
	}
	else if (flag == 'l')
	{
		dup2(var.ofile_fd, 1);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, NULL, 0);
		close(var.in_fd);
	}
	else
	{
		dup2(fds[1], 1);
		close_fd((int[4]){fds[0], fds[1], -1}, NULL, 0);
		close_fd((int[4]){var.ofile_fd, var.in_fd, -1}, NULL, 0);
	}
}
void print_exec_err(char *str1, char *str2)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str2, 2);
}
static void ft_child(t_elem var, int *fds, char *arg, char flag)
{
	char *path;
	char **cmd_arg;

	path = NULL;
	if (flag == 'l' && !var.ofile_fd)
	{
		ft_putendl_fd("pipex: no such file or directory:", 2);
		exit(EXIT_FAILURE);
	}
	cmd_arg = parce_cmd(var, arg, &path);
	if (!cmd_arg)
	{
		close(var.in_fd);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, var.path, 1);
	}
	fds_redirection(fds, var, flag);
	if (execve(path, cmd_arg, NULL) == -1)
	{
		free(path);
		print_exec_err(strerror(errno), cmd_arg[0]);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, cmd_arg, 0);
		close_fd((int[4]){var.in_fd, -1}, var.path, 1);
	}
}

void execute_here_doc_cmd(t_elem var, char *arg, char flag)
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
		close_fd((int [4]){fds[0], fds[1], var.end[0], -1}, var.path, 0);
		close_fd((int[4]){var.end[1], var.in_fd, var.ofile_fd, -1}, NULL, 1);
	}
	else if (var.id == 0)
		ft_child(var, fds, arg, flag);
	if (dup2(fds[0], 0) == -1)
		perror("dup2");
	if (flag == 'h')
		close_fd((int[4]){var.end[1], var.end[0], -1}, NULL, 0);
	close_fd((int[4]){fds[1], fds[0], -1}, NULL, 0);
}
