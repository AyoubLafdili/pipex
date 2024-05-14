/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:26 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 21:56:40 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_sec_path(t_elem vars, char **env)
{
	char *tmp;
	char **path;

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
		path = ft_split(tmp, ':');
		if (!path)
			return(NULL);
		return (path);
	}
	return (NULL);
}

void get_input(int *ends)
{
	char *line;

	if (pipe(ends) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ft_printf("here_doc> ");
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, "here_doc\n", ft_strlen(line)))
			break;
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

void init_struct(t_elem *vars, char **av, char flag)
{
	vars->ofile_fd = check_file(av[vars->ac - 1], flag);
	if (flag != 'h')
		vars->infile = av[1];
	vars->in_fd = dup(0);
	vars->path = get_sec_path(*vars, vars->envp);
	if (!vars->path)
		close_fd((int [4]){vars->ofile_fd, vars->in_fd}, NULL, 1);
}

int apply_herdoc(int argc, char **argv, char **envp)
{
	int		i;
	t_elem	var;

	i = 2;
	get_input(var.end);
	var.envp = envp;
	var.ac = argc;
	init_struct(&var, argv, 'h');
	while (i < argc - 1)
	{
		if (i + 1 == argc - 1)
			execute_here_doc_cmd(var, argv[i], 'l');
		else if (i == 2)
			execute_here_doc_cmd(var, argv[i], 'h');
		else
			execute_here_doc_cmd(var, argv[i], 'n');
		i++;
	}
	while (wait(NULL) != -1)
		;
	dup2(var.in_fd, 0);
	close_fd((int [4]){var.in_fd, var.ofile_fd, -1}, var.path, 0);
	return (0);
}

int multiple_pipes(int ac, char **av, char **envp)
{
	int i;
	t_elem var;
	
	i = 2;
	var.envp = envp;
	var.ac = ac;
	init_struct(&var, av, 'o');
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
	close_fd((int [4]){var.in_fd, var.ofile_fd, -1}, var.path, 0);
	return (0);
}

int	main(int ac, char *av[], char *envp[])
{
	if (ac < 5 || !envp[0])
		return (1);
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		return (apply_herdoc(ac, av, envp));
	return (multiple_pipes(ac, av, envp));
}
