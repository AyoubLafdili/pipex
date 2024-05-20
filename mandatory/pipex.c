/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:50:33 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 10:31:01 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_elem *vars, char **av, char **envp)
{
	vars->outfile_fd = check_file(vars, av[4], 'o');
	vars->args = av;
	vars->infile = av[1];
	vars->in_fd = dup(0);
	vars->path = get_sec_path(envp);
}

int	main(int ac, char *av[], char *envp[])
{
	int		i;
	t_elem	var;

	i = 2;
	if (ac != 5 || !envp[0])
		return (ft_putendl_fd("invalid args", 2), 1);
	init_struct(&var, av, envp);
	execute_cmd(var, av[2], 'f');
	execute_cmd(var, av[3], 'l');
	while (wait(NULL) != -1)
		;
	dup2(var.in_fd, 0);
	close_fd((int [4]){var.in_fd, var.outfile_fd, -1}, var.path, 0);
	return (0);
}
