/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:29 by aradice           #+#    #+#             */
/*   Updated: 2022/10/12 00:54:28 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *error)
{
	perror(error);
	exit (1);
}

void	ft_free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

void	ft_open_files(t_pipex *data, char *infile, char *outfile)
{
	if (data->heredoc == 1)
	{
		ft_here_doc(data);
		data->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (data->outfile == -1)
			ft_error("Outfile Error");
	}
	else
	{		
		data->infile = open(infile, O_RDONLY);
		data->outfile = open(outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (data->outfile == -1 && data->infile == -1)
		{
			perror("Outfile Error");
			ft_error("Infile Error");
		}
		if (data->infile == -1)
			ft_error("Infile Error");
		if (data->outfile == -1)
			ft_error("Outfile Error");
	}
}

void	ft_mode(t_pipex *data, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (argc < 6)
			ft_error("Arguments Error");
		data->index_child = 0;
		data->heredoc = 1;
		data->limiter = argv[2];
		data->commands = argc - 4;
		ft_open_files(data, argv[3], argv[argc - 1]);
		if (unlink("temp.tmp") == -1)
			ft_error("Temp File Error");
	}
	else
	{
		data->index_child = 0;
		data->heredoc = 0;
		data->limiter = NULL;
		data->commands = argc - 3;
		ft_open_files(data, argv[1], argv[argc - 1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc < 5)
		ft_error("Arguments Error");
	else
	{
		ft_mode((&data), argc, argv);
		dup2((&data)->infile, STDIN_FILENO);
		while ((&data)->index_child <= ((&data)->commands) - 1)
		{
			ft_childs(&data, argv, envp);
			(&data)->index_child++;
		}
		while (wait(&(&data)->pid) > 0)
		{
			continue ;
		}
		close((&data)->infile);
		close((&data)->outfile);
	}
	return (0);
}
