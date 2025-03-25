/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:39 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:40 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_parent_process(t_data *data, t_args *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = pip[0];
	if (cmd->next != NULL && cmd->next != data->args && cmd->next->infile == -2)
	{
		cmd->next->infile = pip[0];
		if (cmd->next == NULL)
			printf("cmd->next is NULL\n");
		else
			printf("cmd->next->infile: %d\n", cmd->next->infile);
	}
	else
		close(pip[0]);
}

int	ft_exec_process(t_data *data, t_args *cmd, int *pip)
{
	if (!cmd)
	{
		printf("Error: cmd is NULL in ft_exec_process\n");
		return (-1);
	}
	g_signal_pid = fork();
	if (g_signal_pid < 0)
		ft_free_all(data, "fork error\n", 1);
	else if (!g_signal_pid)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			ft_child_process(data, cmd, pip);
		else
			ft_free_all(data, NULL, 0);
	}
	else
		ft_parent_process(data, cmd, pip);
	return (0);
}

void	ft_wait_process(t_data *data)
{
	int		status;
	int		len;
	int		pid;
	t_args	*temp;

	temp = data->args;
	len = ft_args_size(temp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_signal_pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		if (temp->outfile >= 0)
			close(temp->outfile);
		if (temp->infile >= 0)
			close(temp->infile);
		temp = temp->next;
	}
}

int	ft_exec(t_data *data)
{
	t_args	*temp;
	int		*pip;

	if (data == NULL || data->args->cmd_param[0][0] == '\0')
		return (0);
	if (data->flag_quote != 1)
		ft_check_dollar(data->env, data);
	pip = data->pipe_fd;
	temp = data->args;
	if (ft_is_builtin(temp->cmd_param[0]))
		return ((ft_exec_builtin(0, data, temp), 1));
	if (pipe(pip) == -1)
		return (-1);
	close(pip[0]);
	close(pip[1]);
	ft_exec_process(data, temp, pip);
	temp = temp->next;
	while (temp != data->args)
	{
		if (pipe(pip) == -1)
			return (-1);
		ft_exec_process(data, temp, pip);
		temp = temp->next;
	}
	return (ft_wait_process(data), 1);
}
