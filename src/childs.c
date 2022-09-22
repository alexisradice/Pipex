/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/09/22 22:19:41 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipex *data, char **argv, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		ft_error("Fork Error\n");
	else if (data->pid1 == 0)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		dup2(data->infile, STDIN_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		close(data->infile);
		data->command = ft_split(argv[2], ' ');
		if (execve(ft_path(data, envp), data->command, envp) == -1)
			ft_error("Path or Command Error\n");
	}
}

void	ft_child2(t_pipex *data, char **argv, char **envp)
{
	data->command = ft_split(argv[3], ' ');
	data->pid2 = fork();
	if (data->pid2 < 0)
		ft_error("Fork Error\n");
	else if (data->pid2 == 0)
	{
		dup2(data->pipefd[0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		close(data->outfile);
		if (execve(ft_path(data, envp), data->command, envp) == -1)
			ft_error("Path or Command Error\n");
	}
}
