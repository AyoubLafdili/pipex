/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:51:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/16 21:53:08 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_mtx(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
		free(mtx[i++]);
	free(mtx);
}

void	close_fd(int fds[4], char **to_free, char flag)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (fds[i] == -1)
			break ;
		if (fds[i] != 0)
			close(fds[i]);
		i++;
	}
	if (to_free)
		free_mtx(to_free);
	if (flag)
		exit(EXIT_FAILURE);
}
