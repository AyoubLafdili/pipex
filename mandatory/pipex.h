/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:28:22 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/23 14:45:49 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_element
{
	int		errno_var;
	int		in_fd;
	int		outfile_fd;
	char	*infile;
	char	**args;
	char	**path;
}	t_elem;

void	free_mtx(char **mtx);
char	**get_sec_path(char **env);
void	print_exec_err(char *str1, char *str2);
int		check_file(t_elem *vars, char *str, char flag);
void	execute_cmd(t_elem vars, char *arg, char flag);
char	*ealert(char *msg, char *other, char **to_free);
void	close_fd(int fds[4], char **to_free, char flag);
void	init_struct(t_elem *vars, char **av, char **envp);
char	**parce_cmd(t_elem sec_path, char *arg, char **cmd_path);

#endif