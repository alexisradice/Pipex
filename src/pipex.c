/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:29 by aradice           #+#    #+#             */
/*   Updated: 2022/09/22 03:58:55 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *error, int num_error)
{
	write(2, error, ft_strlen(error));
	exit(num_error);
}

char	**ft_free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	ft_open_files(t_pipex *data, char *infile, char *outfile)
{
	data->infile = open(infile, O_RDONLY);
	data->outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->infile < 0 && data->outfile >= 0)
	{
		close(data->outfile);
		ft_error("Infile Error\n", 0);
	}
	else if (data->outfile < 0 && data->infile >= 0)
	{
		close(data->infile);
		ft_error("Outfile Error\n", 1);
	}
	else if (data->outfile < 0 && data->infile < 0)
		ft_error("Infile and Outfile Error\n", 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		pipefd[2];

	if (argc != 5)
		ft_error("Arguments Error\n", 18);
	else
	{
		if (pipe(pipefd) == -1)
			ft_error("Pipe Error\n", 0);
		ft_open_files(&data, argv[1], argv[argc - 1]);
		ft_child1(&data, pipefd, argv, envp);
		ft_child2(&data, pipefd, argv, envp);
		ft_free_all((&data)->command);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid((&data)->pid1, NULL, 0);
		waitpid((&data)->pid2, NULL, 0);
	}
	return (0);
}
