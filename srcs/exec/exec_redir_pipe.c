/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:45 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/07 14:46:40 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_output_pipe(t_data *data)
{
	int	fd;

	if (data->output_file)
	{
		if (data->redit_output == 1)
			fd = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(data->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_print_error("error output file");
			return ;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	redirect_input_pipe(t_data *data)
{
	int	fd;

	if (data->input_file)
	{
		fd = open(data->input_file, O_RDONLY);
		if (fd == -1)
		{
			ft_print_error("error input file");
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	handle_heredoc_pipe(t_data *data, char *line)
{
	int		pipefd[2];

	if (data->heredoc_delim)
		data->flag_heredoc = 1;
	if (data->flag_heredoc)
	{
		if (pipe(pipefd) == -1)
			exit(EXIT_FAILURE);
		while (1)
		{
			line = readline("> ");
			fflush(stdout);
			if (!line || ft_strcmp(line, data->heredoc_delim) == 0)
			{
				free(line);
				break ;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

void	apply_redirection(t_data *data)
{
	redirect_input_pipe(data);
	handle_heredoc_pipe(data, NULL);
	redirect_output_pipe(data);
}

int	check_next_pipe(t_data **data_pipe, int i, int *fd)
{
	if (data_pipe[i + 1] != NULL)
	{
		if (pipe(fd) == -1)
		{
			ft_print_error("pip");
			return (0);
		}
	}
	return (1);
}
