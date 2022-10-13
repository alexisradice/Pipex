/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:29 by aradice           #+#    #+#             */
/*   Updated: 2022/10/08 23:06:45 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	data->outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1 && data->infile == -1)
	{
		perror("Infile Error");
		perror("Outfile Error");
	}
	else if (data->infile == -1)
		perror("Infile Error");
	else if (data->outfile == -1)
		perror("Outfile Error");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
		ft_message("Error: Arguments");
	else
	{
		if (pipe((&data)->pipefd) == -1)
			ft_error("Pipe Error");
		ft_open_files(&data, argv[1], argv[argc - 1]);
		ft_child1(&data, argv, envp);
		ft_child2(&data, argv, envp);
		ft_free_all((&data)->command);
		close((&data)->pipefd[0]);
		close((&data)->pipefd[1]);
		if ((&data)->infile != -1)
			close((&data)->infile);
		if ((&data)->outfile != -1)
			close((&data)->outfile);
		waitpid((&data)->pid1, NULL, 0);
		waitpid((&data)->pid2, NULL, 0);
	}
	return (0);
}
