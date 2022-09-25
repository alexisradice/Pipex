/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:11:32 by aradice           #+#    #+#             */
/*   Updated: 2022/09/25 18:46:02 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		infile;
	int		outfile;
	char	**command;
	char	**paths;
	char	*path;
	char	*command_path;
	int		*pipefd;
	int		index_child;
}				t_pipex;

void	ft_error(char *error);
char	**ft_free_all(char **tab);
void	ft_open_files(t_pipex *data, char *infile, char *outfile);
void	ft_childs(t_pipex *data, int argc, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);
char	*ft_access(t_pipex *data);
char	*ft_path(t_pipex *data, char **envp);

#endif