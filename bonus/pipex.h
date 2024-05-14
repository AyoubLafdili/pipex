/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:22 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 11:43:53 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_element
{
	char **argv;
	int argc;
	int		ofile_fd;
	int		in_fd;
	char	*infile;
	char	**path;
}	t_elem;

char	**parce_cmd(t_elem sec_path, char *arg, char **cmd_path);
void	free_mtx(char **mtx);
int		check_file(char *str, char flag);
void	execute_cmd(t_elem vars, char *arg, char flag);
void 	close_fd(int fds[4], char **to_free, char flag);
char *ealert(char *msg, char *other, char **to_free);

#endif