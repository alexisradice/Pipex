/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:11:32 by aradice           #+#    #+#             */
/*   Updated: 2022/09/23 23:18:26 by aradice          ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	char	**command;
	char	**paths;
	char	*path;
	char	*command_path;
	int		pipefd[2];
}				t_pipex;

void	ft_error(char *error);
char	**ft_free_all(char **tab);
void	ft_open_files(t_pipex *data, char *infile, char *outfile);
void	ft_child1(t_pipex *data, char **argv, char **envp);
void	ft_child2(t_pipex *data, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);
char	*ft_access(t_pipex *data);
char	*ft_path(t_pipex *data, char **envp);

#endif