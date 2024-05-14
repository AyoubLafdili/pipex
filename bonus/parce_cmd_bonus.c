/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:14:31 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/12 16:43:55 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *check_path(t_elem vars, char *arg)
{
	int i;
	char *path;
	char *tmp;

	i = 0;
	path = NULL;
	tmp = NULL;
	while (vars.path[i])
	{
		tmp = ft_strjoin(vars.path[i], "/");
		if (!tmp)
			return ("");
		path = ft_strjoin(tmp, arg);
		if (!path)
			return (free(tmp), "");
		free(tmp);
		if (!access(path, F_OK))
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	return (NULL);
}

char *ealert(char *msg, char *other, char **to_free)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (other)
		ft_putendl_fd(other, 2);
	if (to_free)
		free_mtx(to_free);
	return (NULL);
}

char **parce_cmd(t_elem sec_path, char *arg, char **cmd_path)
{
	char **cmd_opt;

	if (arg[0] == '\0')
		return (ealert("pipex: permission denied:\n", NULL, NULL), NULL);
	cmd_opt = ft_split(arg, ' ');
	if (!cmd_opt)
		return (NULL);
	if (cmd_opt[0][0] == '/' || (cmd_opt[0][0] == '.' && cmd_opt[0][1] == '/'))
	{
		if (access(cmd_opt[0], F_OK) == -1)
		{
			ealert("pipex: no such file or directory: ", cmd_opt[0], cmd_opt);
			return (NULL);
		}
		*cmd_path = cmd_opt[0];
		return (cmd_opt);
	}
	*cmd_path = check_path(sec_path, cmd_opt[0]);
	if (*cmd_path == NULL)
	   return (ealert("pipex: command not found: ", cmd_opt[0], cmd_opt), NULL);
	else if (**cmd_path == '\0')
		return (free_mtx(cmd_opt), NULL);
	return (cmd_opt);
}
