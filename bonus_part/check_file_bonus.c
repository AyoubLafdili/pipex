/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:59:32 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/17 18:21:38 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_file(t_elem *vars, char *str, char flag)
{
	int	fd;

	if (flag == 'h')
	{
		fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (vars->errno_var = errno, 0);
		return (fd);
	}
	else if (flag == 'i')
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				return (ealert("pipex: permission denied: ", str, NULL), 0);
			return (ealert("pipex: no such file or directory: ", str, NULL), 0);
		}
		return (fd);
	}
	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (vars->errno_var = errno, 0);
	return (fd);
}
