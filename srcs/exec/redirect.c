/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:56 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/07 14:55:16 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_open_redirect(t_data *data, int append)
{
	int	fd;

	if (append)
		fd = open(data->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(data->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	ft_redirect(t_data *data, int append)
{
	int	fd;
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (original_stdout < 0)
	{
		perror("Error duplicating stdout");
		return (1);
	}
	fd = ft_open_redirect(data, append);
	if (fd < 0)
	{
		ft_print_error("minishell :syntax error near unexpected \
token `newline'\n");
		close(original_stdout);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Error dup2");
		close(fd);
		close(original_stdout);
		return (1);
	}
	close(fd);
	return (original_stdout);
}

int	redirect_output(t_data *data, int append)
{
	int	original_stdout;

	original_stdout = ft_redirect(data, append);
	if (original_stdout == 1)
		return (1);
	ft_exec(data);
	if (dup2(original_stdout, STDOUT_FILENO) < 0)
	{
		perror("Error restoring stdout");
		close(original_stdout);
		return (1);
	}
	close(original_stdout);
	return (0);
}

int	ft_open_and_redirect_input(t_data *data)
{
	int	fd;

	fd = open(data->input_file, O_RDONLY);
	if (fd < 0)
	{
		ft_print_error("minishell: syntax error near unexpected \
token `newline'\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	execute_with_redirection(t_data *data)
{
	if (data->redit_output == 1 && !data->flag_heredoc
		&& data->flag_pipe == 0)
	{
		if (redirect_output(data, 0) == 1)
			return (0);
	}
	else if (data->redit_output == 2 && !data->flag_heredoc
		&& data->flag_pipe == 0)
	{
		if (redirect_output(data, 1) == 1)
			return (0);
	}
	if (data->flag_input == 1 && data->flag_pipe == 0)
	{
		if (redirect_input(data) == 1)
			return (0);
	}
	if (data->flag_heredoc == 1 && data->flag_pipe == 0)
	{
		if (heredoc(data->heredoc_delim, data) == 1 && data->flag_pipe == 0)
			return (0);
	}
	return (1);
}
