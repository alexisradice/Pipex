/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:39 by aradice           #+#    #+#             */
/*   Updated: 2022/10/08 23:06:21 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_access(t_pipex *data)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	// if (access(data->command[0], F_OK | X_OK) == 0)
	// 	return (data->command[0]);
	// while (data->paths[i])
	// {
	// 	// temp = data->paths[i];
	// 	// free(data->paths[i]);
	// 	data->paths[i] = ft_strjoin(data->paths[i], "/");
	// 	// free(temp);
	// 	i++;
	// }
	// i = 0;
	while (data->paths[i])
	{
		// printf("%s", data->command[0]);
		temp = ft_strjoin(data->paths[i], "/");
		// temp = data->paths[i];
		temp2 = ft_strjoin(temp, data->command[0]);
		free(temp);
		if (access(temp2, F_OK | X_OK) == 0)
		{
			ft_free_all(data->paths);
			data->command_path = temp2;
			free(temp2);
			printf("%s", data->command_path);
			return ;
		}
		free(temp2);
		i++;
	}
	ft_free_all(data->paths);
}

void	ft_path(t_pipex *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			data->path = ft_substr(envp[i], i, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	data->paths = ft_split(data->path, ':');
	if (!data->paths)
		exit(1);
	// ft_free_all(data->paths);
	free(data->path);
	ft_access(data);
}
