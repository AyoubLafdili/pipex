/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sec_path_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:49:30 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/16 21:53:08 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_sec_path(char **env)
{
	char	*tmp;
	char	**path;

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
			return (NULL);
		return (path);
	}
	return (NULL);
}
