/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/09/25 19:44:01 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	ft_child1(t_pipex *data, char **argv, char **envp)
// {
// 	data->pid1 = fork();
// 	if (data->pid1 == -1)
// 		ft_error("Fork Error");
// 	else if (data->pid1 == 0)
// 	{
// 		dup2(data->pipefd[1], STDOUT_FILENO);
// 		dup2(data->infile, STDIN_FILENO);
// 		close(data->pipefd[0]);
// 		close(data->pipefd[1]);
// 		data->command = ft_split(argv[2], ' ');
// 		if (execve(ft_path(data, envp), data->command, envp) == -1)
// 			ft_error("Path or Command Error");
// 	}
// }

// void	ft_child2(t_pipex *data, char **argv, char **envp)
// {
// 	data->command = ft_split(argv[3], ' ');
// 	data->pid2 = fork();
// 	if (data->pid2 == -1)
// 		ft_error("Fork Error\n");
// 	else if (data->pid2 == 0)
// 	{
// 		dup2(data->pipefd[0], STDIN_FILENO);
// 		dup2(data->outfile, STDOUT_FILENO);
// 		close(data->pipefd[0]);
// 		close(data->pipefd[1]);
// 		if (execve(ft_path(data, envp), data->command, envp) == -1)
// 			ft_error("Path or Command Error");
// 	}
// }

void	ft_childs(t_pipex *data, int argc, char **argv, char **envp)
{
	int	readfd;
	int	writefd;
	int	i;

	i = 0;
	readfd = data->pipefd[2 * data->index_child - 2];
	writefd = data->pipefd[2 * data->index_child + 1];
	data->pid = fork();
	if (data->pid == -1)
		ft_error("Fork Error");
	if (data->pid == 0)
	{
		if (data->index_child == 0)
		{
			dup2(data->infile, STDIN_FILENO);
			dup2(writefd, STDOUT_FILENO);
		}
		else if (data->index_child == argc - 3 - 1)
		{
			dup2(readfd, STDIN_FILENO);
			dup2(data->outfile, STDOUT_FILENO);
		}
		else
		{
			dup2(readfd, STDIN_FILENO);
			dup2(writefd, STDOUT_FILENO);
		}	
		while (i < argc - 3 - 1)
		{
			close(data->pipefd[i]);
			i++;
		}
		printf("test; %s",argv[2 + data->index_child]);
		data->command = ft_split(argv[2 + data->index_child], ' ');
		if (execve(ft_path(data, envp), data->command, envp) == -1)
			ft_error("Path or Command Error");
	}
}
