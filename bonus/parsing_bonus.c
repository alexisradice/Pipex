/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:39 by aradice           #+#    #+#             */
/*   Updated: 2022/09/25 19:01:10 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_access(t_pipex *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->paths[i])
	{
		temp = data->paths[i];
		data->paths[i] = ft_strjoin(data->paths[i], "/");
		free(temp);
		i++;
	}
	i = 0;
	while (data->paths[i])
	{
		data->command_path = ft_strjoin(data->paths[i], data->command[0]);
		if (access(data->command_path, F_OK | X_OK) == 0)
		{
			ft_free_all(data->paths);
			return (data->command_path);
		}
		free(data->command_path);
		i++;
	}
	ft_free_all(data->paths);
	return (NULL);
}

char	*ft_path(t_pipex *data, char **envp)
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
		return (NULL);
	free(data->path);
	return (ft_access(data));
}
