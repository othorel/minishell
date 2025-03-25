/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:49 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 09:35:00 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_heredoc(const char *delimiter)
{
	char	*buffer;
	int		fd;

	fd = open("heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer || g_signal_pid)
			break ;
		if (ft_strncmp(buffer, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	free(buffer);
	close(fd);
}

void	cpy_to_output(char *output_file, t_data *data)
{
	int		fd_output;
	int		fd_input;
	char	buffer[1024];
	int		byte_read;

	fd_input = open("heredoc.tmp", O_RDONLY);
	if (fd_input < 0)
		exit (1);
	if (data->redit_output == 1)
		fd_output = open(output_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd_output = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_output < 0)
		exit (1);
	byte_read = read(fd_input, buffer, sizeof(buffer));
	while (byte_read > 0)
		write(fd_output, buffer, byte_read);
	close(fd_input);
	close(fd_output);
}

void	exec_cmd_with_heredoc(t_data *data)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open("heredoc.tmp", O_RDONLY);
		if (fd < 0)
			exit (1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_exec(data);
		exit(1);
	}
	else
		waitpid(pid, NULL, 0);
}

int	heredoc(const char *delimiter, t_data *data)
{
	pid_t	pid;
	int		status;

	(void)data;
	if (!delimiter || *delimiter == '\0')
		return (ft_print_error("minishell: syntax error near unexpected \
token `newline'\n"), 1);
	pid = fork();
	if (pid == 0)
	{
		do_heredoc(delimiter);
		exit(0);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, SIG_DFL);
		exec_cmd_with_heredoc(data);
	}
	if (data->output_file)
		cpy_to_output(data->output_file, data);
	unlink("heredoc.tmp");
	return (0);
}
