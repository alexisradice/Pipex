/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/10/08 23:06:33 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_init(t_pipex *data, char **envp)
{
	if (data->command == NULL)
		exit(1);
	data->correct_path = ft_path(data, envp);
	if (data->correct_path == NULL)
	{
		ft_free_all(data->command);
		free(data->correct_path);
		ft_message("Error: Command not found\n");
	}
}

void	ft_child1(t_pipex *data, char **argv, char **envp)
{
	data->pid1 = fork();
	if (data->pid1 == -1)
		ft_error("Fork Error");
	else if (data->pid1 == 0)
	{
		if (data->infile == -1)
			exit(1);
		dup2(data->pipefd[1], STDOUT_FILENO);
		dup2(data->infile, STDIN_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		data->command = ft_split(argv[2], ' ');
		ft_exec_init(data, envp);
		execve(data->correct_path, data->command, envp);
	}
}

void	ft_child2(t_pipex *data, char **argv, char **envp)
{
	data->command = ft_split(argv[3], ' ');
	data->pid2 = fork();
	if (data->pid2 == -1)
		ft_error("Fork Error");
	else if (data->pid2 == 0)
	{
		if (data->outfile == -1)
		{
			ft_free_all(data->command);
			exit(1);
		}
		dup2(data->pipefd[0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		ft_exec_init(data, envp);
		execve(ft_path(data, envp), data->command, envp);
	}
}
