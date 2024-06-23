/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 21:52:06 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/23 14:46:01 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_element
{
	int		in_fd;
	int		ac;
	int		outfile_fd;
	int		infile_fd;
	int		errno_var;
	int		end[2];
	char	**args;
	char	**envp;
	char	**path;
}	t_elem;

void	free_mtx(char **mtx);
char	**get_sec_path(char **env);
void	print_exec_err(char *str1, char *str2);
int		ft_strcmp(char *s1, char *s2, int *end);
int		check_file(t_elem *vars, char *str, char flag);
void	execute_cmd(t_elem vars, char *arg, char flag);
char	*ealert(char *msg, char *other, char **to_free);
void	close_fd(int fds[4], char **to_free, char flag);
int		apply_heredoc(int argc, char **argv, char **envp);
void	execute_here_doc_cmd(t_elem var, char *arg, char flag);
void	init_struct(t_elem *vars, char **av, int ac, char flag);
char	**parce_cmd(t_elem sec_path, char *arg, char **cmd_path);

#endif