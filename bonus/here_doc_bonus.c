/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:29:02 by aradice           #+#    #+#             */
/*   Updated: 2022/10/08 18:22:29 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_here_doc(t_pipex *data)
{
	char	*line;
	int		temp;

	temp = open("temp.tmp", O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (temp == -1)
		ft_error("File Error");
	line = get_next_line(STDIN_FILENO);
	while (1)
	{
		if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter)))
		{
			if (ft_strlen(data->limiter) == ft_strlen(line) - 1)
			{
				close(temp);
				free(line);
				data->infile = open("temp.tmp", O_RDONLY);
				break ;
			}
		}
		write(temp, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	if (unlink("temp.tmp") == -1)
		ft_error("Temp File Error");
}