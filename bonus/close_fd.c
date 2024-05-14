/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 21:44:53 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/11 21:49:32 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fd(int fds[4], char **to_free, char flag)
{
	int i = 0;
	while (i < 4)
	{
		if (fds[i] == -1)
			break ;
		close(fds[i]);
		i++;
	}
	if (to_free)
		free_mtx(to_free);
    if (flag)
        exit(EXIT_FAILURE);
}
