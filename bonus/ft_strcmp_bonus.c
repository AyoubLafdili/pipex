/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:56:54 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/18 12:26:15 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	del_new_line(char *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i] != '\n' && line)
		i++;
	line[i] = '\0';
}

int	ft_strcmp(char *s1, char *s2, int *end)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(s1);
	if (!tmp)
	{
		free(s1);
		close_fd((int [4]){end[0], end[1], -1}, NULL, 1);
	}
	del_new_line(tmp);
	while (tmp[i] || s2[i])
	{
		if (tmp[i] != s2[i])
		{
			i = tmp[i] - s2[i];
			return (free(tmp), i);
		}
		i++;
	}
	return (free(tmp), free(s1), 0);
}
