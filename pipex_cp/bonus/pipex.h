/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:22 by alafdili          #+#    #+#             */
/*   Updated: 2024/05/14 21:49:55 by alafdili         ###   ########.fr       */
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
	int 	ac;
	char	**envp;
	int 	end[2];
	int		ofile_fd;
	int		infile_fd;
	int		in_fd;
	pid_t	id;
	char	*infile;
	char	**path;
}	t_elem;

void	free_mtx(char **mtx);
int		check_file(char *str, char flag);
void	print_exec_err(char *str1, char *str2);
void	execute_cmd(t_elem vars, char *arg, char flag);
char 	*ealert(char *msg, char *other, char **to_free);
void 	close_fd(int fds[4], char **to_free, char flag);
void	execute_here_doc_cmd(t_elem var, char *arg, char flag);
char	**parce_cmd(t_elem sec_path, char *arg, char **cmd_path);

#endif