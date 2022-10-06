/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/10/05 20:33:48 by aradice          ###   ########.fr       */
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
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT_FILENO);
		if (data->heredoc == 1)
			data->command = ft_split(argv[3 + data->index_child], ' ');
		else
			data->command = ft_split(argv[2 + data->index_child], ' ');
		if (execve(ft_path(data, envp), data->command, envp) == -1)
			ft_error("Path or Commxand Error");
	}
	else
	{
		close(data->pipefd[1]);
		dup2(data->pipefd[0], STDIN_FILENO);
		waitpid(data->pid, NULL, 0);
	}
}
