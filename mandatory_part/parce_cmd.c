/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:14:31 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 14:43:00 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(t_elem vars, char *arg)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	path = NULL;
	tmp = NULL;
	if (!vars.path)
		return (NULL);
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

char	*ealert(char *msg, char *other, char **to_free)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (other)
		ft_putendl_fd(other, 2);
	if (to_free)
		free_mtx(to_free);
	return (NULL);
}

char	**parce_cmd(t_elem sec_path, char *arg, char **cmd_path)
{
	char	**cmdopt;

	*cmd_path = NULL;
	if (arg[0] == '\0')
		return (ealert("pipex: permission denied:\n", NULL, NULL), NULL);
	cmdopt = ft_split(arg, ' ');
	if (!cmdopt || !cmdopt[0])
		return (ealert("pipex: command not found:\n", NULL, cmdopt), NULL);
	if (cmdopt[0][0] == '/' || (cmdopt[0][0] == '.' && cmdopt[0][1] == '/'))
	{
		if (access(cmdopt[0], F_OK) == -1)
		{
			ealert("pipex: no such file or directory: ", cmdopt[0], cmdopt);
			return (NULL);
		}
		*cmd_path = cmdopt[0];
		return (cmdopt);
	}
	*cmd_path = check_path(sec_path, cmdopt[0]);
	if (*cmd_path == NULL)
		return (ealert("pipex: command not found: ", cmdopt[0], cmdopt), NULL);
	else if (**cmd_path == '\0')
		return (free_mtx(cmdopt), NULL);
	return (cmdopt);
}
