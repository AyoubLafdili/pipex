/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:26 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 13:07:09 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct(t_elem *vars, char **av, int ac, char flag)
{
	vars->outfile_fd = check_file(vars, av[ac - 1], flag);
	vars->ac = ac;
	vars->args = av;
	vars->in_fd = dup(0);
	vars->path = get_sec_path(vars->envp);
}

int	multiple_pipes(int ac, char **av, char **envp)
{
	int		i;
	t_elem	var;

	i = 2;
	var.envp = envp;
	init_struct(&var, av, ac, 'o');
	while (i < ac - 1)
	{
		if (i + 1 == ac - 1)
			execute_cmd(var, av[i], 'l');
		else if (i == 2)
			execute_cmd(var, av[i], 'f');
		else
			execute_cmd(var, av[i], 'n');
		i++;
	}
	while (wait(NULL) != -1)
		;
	dup2(var.in_fd, 0);
	close_fd((int [4]){var.in_fd, var.outfile_fd, -1}, var.path, 0);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac < 5 || !envp[0])
		return (ft_putendl_fd("invalid args", 2), 1);
	if (ft_strlen(av[1]) == 8 && !ft_strncmp(av[1], "here_doc", 8))
		return (apply_heredoc(ac, av, envp));
	return (multiple_pipes(ac, av, envp));
}
