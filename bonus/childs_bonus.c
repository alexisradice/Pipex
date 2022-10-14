/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/10/13 16:46:35 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_childs(t_pipex *data, char **argv, char **envp)
{
	if (pipe(data->pipefd) == -1)
		ft_error("Pipe Error");
	data->pid = fork();
	if (data->pid == -1)
		ft_error("Fork Error");
	if (data->pid == 0)
	{
		if (data->infile == -1 && data->index_child == 0)
			exit(1);
		if (data->outfile == -1 && data->index_child == data->commands - 1)
			exit(1);
		close(data->pipefd[0]);
		if (data->index_child == data->commands - 1)
			dup2(data->outfile, STDOUT_FILENO);
		else
			dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[1]);
		ft_exec_init(data, argv, envp);
		execve(data->correct_path, data->command, envp);
	}
	close(data->pipefd[1]);
	dup2(data->pipefd[0], STDIN_FILENO);
	close(data->pipefd[0]);
}

void	ft_exec_init(t_pipex *data, char **argv, char **envp)
{
	if (data->heredoc == 1)
		data->command = ft_split(argv[3 + data->index_child], ' ');
	else
		data->command = ft_split(argv[2 + data->index_child], ' ');
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

void	ft_error(char *error)
{
	perror(error);
	exit (1);
}

void	ft_message(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}
