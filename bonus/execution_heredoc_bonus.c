/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_heredoc_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:56:18 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 14:26:52 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	fds_redirection(t_elem var, int fds[2], char flag)
{
	if (flag == 'h')
	{
		dup2(var.end[0], 0);
		dup2(fds[1], 1);
		close_fd((int [4]){var.end[0], var.end[1], fds[0], -1}, NULL, 0);
		close_fd((int [4]){fds[1], var.outfile_fd, var.in_fd, -1}, NULL, 0);
	}
	else if (flag == 'l')
	{
		dup2(var.outfile_fd, 1);
		close_fd((int [4]){fds[0], fds[1], var.outfile_fd, -1}, NULL, 0);
		close(var.in_fd);
	}
	else
	{
		dup2(fds[1], 1);
		close_fd((int [4]){fds[0], fds[1], -1}, NULL, 0);
		close_fd((int [4]){var.outfile_fd, var.in_fd, -1}, NULL, 0);
	}
}

void	print_exec_err(char *str1, char *str2)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str2, 2);
}

static void	ft_child(t_elem var, int *fds, char *arg, char flag)
{
	char	*path;
	char	**cmd_arg;

	if (flag == 'l' && !var.outfile_fd)
	{
		if (var.errno_var == EACCES)
			ealert("pipex: permission denied: ", var.args[var.ac - 1], NULL);
		else
			ft_putendl_fd("pipex: no such file or directory:", 2);
		dup2(var.in_fd, 0);
		close_fd((int [4]){fds[0], fds[1], var.in_fd, -1}, var.path, 1);
	}
	cmd_arg = parce_cmd(var, arg, &path);
	if (!cmd_arg)
	{
		close(var.in_fd);
		close_fd((int [4]){fds[0], fds[1], var.outfile_fd, -1}, var.path, 1);
	}
	fds_redirection(var, fds, flag);
	if (execve(path, cmd_arg, NULL) == -1)
	{
		print_exec_err(strerror(errno), cmd_arg[0]);
		close_fd((int [4]){fds[0], fds[1], var.outfile_fd, -1}, cmd_arg, 0);
		close_fd((int [4]){var.in_fd, -1}, var.path, 1);
	}
}

void	execute_here_doc_cmd(t_elem var, char *arg, char flag)
{
	int		fds[2];
	pid_t	id;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		dup2(var.in_fd, 0);
		close_fd((int [4]){var.in_fd, var.outfile_fd, -1}, var.path, 1);
	}
	id = fork();
	if (id == -1)
	{
		perror("fork");
		dup2(var.in_fd, 0);
		close_fd((int [4]){fds[0], fds[1], var.end[0], -1}, var.path, 0);
		close_fd((int [4]){var.end[1], var.in_fd, var.outfile_fd, -1}, NULL, 1);
	}
	else if (id == 0)
		ft_child(var, fds, arg, flag);
	dup2(fds[0], 0);
	if (flag == 'h')
		close_fd((int [4]){var.end[1], var.end[0], -1}, NULL, 0);
	close_fd((int [4]){fds[1], fds[0], -1}, NULL, 0);
}
