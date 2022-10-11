/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:11:32 by aradice           #+#    #+#             */
/*   Updated: 2022/10/09 20:16:06 by aradice          ###   ########.fr       */
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
	int		pipefd[2];
	int		index_child;
	int		heredoc;
	char 	*limiter;
	int		commands;
}				t_pipex;

void	ft_error(char *error);
void	ft_free_all(char **tab);
void	ft_open_files(t_pipex *data, char *infile, char *outfile);
void	ft_childs(t_pipex *data, char **argv, char **envp);
int		main(int argc, char **argv, char **envp);
void	ft_access(t_pipex *data);
void	ft_path(t_pipex *data, char **envp);
void	ft_mode(t_pipex *data, int argc, char **argv);
void	ft_here_doc(t_pipex *data);

#endif