/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:26 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 12:08:42 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void get_sec_path(t_elem *vars, char **env)
{
	char *tmp;
	
	tmp = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
		{
			tmp = *env;
			break ;
		}
		env++;
	}
	if (tmp)
	{
		tmp += 5;
		vars->path = ft_split(tmp, ':');
		if (!vars->path)
			close_fd((int [4]){vars->ofile_fd, -1}, NULL, 1);
		return ;
	}
	close_fd((int [4]){vars->ofile_fd, -1}, NULL, 1);
}

void init_struct(t_elem *vars, char *out, char *in, char flag)
{
	vars->ofile_fd = check_file(out, flag);
	vars->infile = in;
	vars->in_fd = 0;
	vars->path = NULL;
}

void apply_herdoc(t_elem var, int argc, char **argv, char **envp)
{
	int		i;

	i = 2;
	init_struct(&var, argv[argc - 1], NULL, 'h');
	get_sec_path(&var, envp);
	while (i < argc - 1)
	{
		if (i + 1 == argc - 1)
			execute_cmd(var, argv[i], 'l');
		else if (i == 2)
			execute_cmd(var, argv[i], 'h');
		else
			execute_cmd(var, argv[i], 'n');
		i++;
	}
	
	while (wait(NULL) != -1)
		;
	exit(EXIT_SUCCESS);
}

int	main(int ac, char *av[], char *envp[])
{
	t_elem var = {0};
	int i;

	if (ac < 5 || !envp[0])
		return (1);
	i = 2;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		apply_herdoc(var, ac, av, envp);
	// init_struct(&var, av[ac - 1], av[1], 'o');
	// get_sec_path(&var, envp);
	// var.in_fd = dup(0);
	// while (i < ac - 1)
	// {
	// 	if (i + 1 == ac - 1)
	// 		execute_cmd(var, av[i], 'l');
	// 	else if (i == 2)
	// 		execute_cmd(var, av[i], 'f');
	// 	else
	// 		execute_cmd(var, av[i], 'n');
	// 	i++;
	// }
	// while (wait(NULL) != -1)
	// 	;
	// dup2(var.in_fd, 0);
	// close_fd((int [4]){var.in_fd, var.ofile_fd, -1}, var.path, 0);
}
