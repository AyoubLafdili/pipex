/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:03:25 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 13:09:24 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_input(char *limiter, int *ends)
{
	char	*line;

	if (pipe(ends) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ft_printf("here_doc> ");
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter, ends))
			break ;
		ft_printf("here_doc> ");
		if (write(ends[1], line, ft_strlen(line)) == -1)
		{
			perror("write");
			close_fd((int [4]){ends[0], ends[1], -1}, NULL, 1);
		}
		free(line);
		line = NULL;
	}
}

int	apply_heredoc(int argc, char **argv, char **envp)
{
	int		i;
	t_elem	var;

	i = 3;
	get_input(argv[2], var.end);
	var.envp = envp;
	init_struct(&var, argv, argc, 'h');
	while (i < argc - 1)
	{
		if (i + 1 == argc - 1)
			execute_here_doc_cmd(var, argv[i], 'l');
		else if (i == 3)
			execute_here_doc_cmd(var, argv[i], 'h');
		else
			execute_here_doc_cmd(var, argv[i], 'n');
		i++;
	}
	while (wait(NULL) != -1)
		;
	dup2(var.in_fd, 0);
	close_fd((int [4]){var.in_fd, var.outfile_fd, -1}, var.path, 0);
	return (0);
}
