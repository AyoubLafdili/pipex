/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:02:21 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 12:09:04 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void fds_redirection(int fds[2], t_elem var, char flag)
{
	int in_fd;
	char *line;

	if (flag == 'h')
	{
		int ends[2];

		pipe(ends);
		ft_printf("here_doc> ");
		while (1)
		{
			line = get_next_line(0);
			if (!line || !ft_strncmp(line, "here_doc\n", ft_strlen(line)))
				break;
			ft_printf("here_doc> ");
			write(ends[1], line, ft_strlen(line));
			free(line);
			line = NULL;
		}
		dup2(ends[0], 0);
		dup2(fds[1], 1);
		close(ends[1]);
		close(ends[0]);
		close(fds[1]);
		close(fds[0]);
	}
	else if (flag == 'f')
	{
		in_fd = check_file(var.infile, 'i');
		if (!in_fd)
			close_fd((int[4]){fds[0], fds[1], -1}, NULL, 1);
		else
		{
			dup2(in_fd, 0);
			dup2(fds[1], 1);
			close_fd((int[4]){fds[0], fds[1], -1}, NULL, 0);
		}
	}
	else if (flag == 'l')
	{
		dup2(var.ofile_fd, 1);
		close_fd((int[4]){fds[1], fds[0], var.ofile_fd, -1}, NULL, 0);
	}
	else
	{
		dup2(fds[1], 1);
		close_fd((int[4]){fds[0], fds[1], -1}, NULL, 0);
	}
}

void ft_child(int fds[2], t_elem var, char *arg, char flag)
{
	char *path;
	char **cmd_arg;


	path = NULL;
	fds_redirection(fds, var, flag);
	cmd_arg = parce_cmd(var, arg, &path);
	if (!cmd_arg)//  /!\   note:
	{
		close(var.in_fd);///
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, var.path, 1);
	}
	if (execve(path, cmd_arg, NULL) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(cmd_arg[0], 2);
		close_fd((int[4]){fds[0], fds[1], var.ofile_fd, -1}, cmd_arg, 0);
		free_mtx(var.path);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void execute_cmd(t_elem var, char *arg, char flag)
{
	int fds[2];
	pid_t new_p;

	if (pipe(fds) == -1)
	{
		perror("pipe");
		dup2(var.in_fd, 0);
		close_fd((int[4]){var.in_fd, var.ofile_fd, -1}, var.path, 1);
	}
	new_p = fork();
	if (new_p == -1)
	{
		perror("fork");
		dup2(var.in_fd, 0);
		close_fd((int[4]){var.in_fd, var.ofile_fd, -1}, var.path, 1);
	}
	else if (new_p == 0)
		ft_child(fds, var, arg, flag);
	else
	{
		if (dup2(fds[0], 0) == -1)
			perror("dup2");
		close_fd((int[4]){fds[1], fds[0], -1}, NULL, 0);
	}
}
