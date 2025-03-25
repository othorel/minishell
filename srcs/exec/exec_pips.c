/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pips.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:42 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 13:15:51 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	final_exec_pip(t_data *data, t_data **data_pipe, t_pipex *pipex)
{
	char	*cmd_path;

	cmd_path = ft_exec_command(data_pipe[pipex->i],
			data_pipe[pipex->i]->args->cmd_param[0], data->env);
	if (!cmd_path)
	{
		ft_command_not_found(cmd_path, data);
		exit(EXIT_FAILURE);
	}
	if (ft_is_builtin(data_pipe[pipex->i]->args->cmd_param[0]))
		ft_exec_builtin(0, data_pipe[pipex->i], data_pipe[pipex->i]->args);
	else
		execve(cmd_path, data_pipe[pipex->i]->args->cmd_param, NULL);
	if (cmd_path)
		free(cmd_path);
	free_data_pipe(data_pipe);
	ft_free_list(&data->env);
	ft_free_data(data);
	free(pipex);
	exit(EXIT_FAILURE);
}

static void	create_pipe(t_data **data_pipe, int i, int fd[2])
{
	if (!check_next_pipe(data_pipe, i, fd))
		exit(EXIT_FAILURE);
}

static void	handle_child_proc(t_data *data, t_data **data_pipe, t_pipex *pipex)
{
	if (pipex->i > 0)
	{
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		{
			exit(EXIT_FAILURE);
		}
		close(pipex->in_fd);
	}
	if (data_pipe[pipex->i + 1] != NULL)
	{
		if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	apply_redirection(data_pipe[pipex->i]);
	final_exec_pip(data, data_pipe, pipex);
}

static void	handle_parent_process(t_pipex *pipex, t_data **data_pipe)
{
	if (pipex->i > 0)
		close(pipex->in_fd);
	if (data_pipe[pipex->i + 1] != NULL)
	{
		close(pipex->fd[1]);
		pipex->in_fd = pipex->fd[0];
	}
	else
		close(pipex->fd[0]);
	waitpid(pipex->pid, NULL, WNOHANG);
}

int	execute_pipeline(t_data *data, t_data **data_pipe)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	ft_memset(pipex, 0, sizeof(t_pipex));
	if (!data_pipe[1])
		return (1);
	while (data_pipe[pipex->i] != NULL)
	{
		create_pipe(data_pipe, pipex->i, pipex->fd);
		pipex->pid = fork();
		if (pipex->pid < 0)
			return (exit(EXIT_FAILURE), 0);
		else if (pipex->pid == 0)
			handle_child_proc(data, data_pipe, pipex);
		else
			handle_parent_process(pipex, data_pipe);
		pipex->i++;
	}
	while (wait(NULL) > 0)
		continue ;
	close(pipex->in_fd);
	free_pipe_data(data_pipe);
	if (pipex)
		free(pipex);
	return (1);
}
