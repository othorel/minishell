/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:53 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:54 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_builtin(int stdout, t_data *data, t_args *cmd)
{
	if (!ft_strcmp("pwd", cmd->cmd_param[0]))
		data->exit_code = ft_pwd();
	else if (!ft_strcmp("echo", cmd->cmd_param[0]))
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (!ft_strcmp("cd", cmd->cmd_param[0]))
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (!ft_strcmp("export", cmd->cmd_param[0]))
		data->exit_code = ft_export(cmd->cmd_param, &data->env);
	else if (!ft_strcmp("unset", cmd->cmd_param[0]))
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (!ft_strcmp("env", cmd->cmd_param[0]))
		data->exit_code = ft_env(data->env);
	else if (!ft_strcmp("exit", cmd->cmd_param[0]))
	{
		if (stdout != -1 && stdout != 1)
		{
			dup2(stdout, 1);
			close(stdout);
		}
		ft_exit(data, data->args->cmd_param, 0);
	}
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}

int	ft_restore_and_exec_input(t_data *data, int original_stdin)
{
	if (dup2(original_stdin, STDIN_FILENO) < 0)
	{
		perror("Error restoring stdin");
		return (1);
	}
	close(original_stdin);
	ft_exec(data);
	return (0);
}

int	redirect_input(t_data *data)
{
	int	original_stdin;

	original_stdin = dup(STDIN_FILENO);
	if (original_stdin < 0)
	{
		perror("Error dup stdin");
		return (1);
	}
	if (ft_open_and_redirect_input(data) < 0)
	{
		close(original_stdin);
		return (1);
	}
	ft_exec(data);
	return (ft_restore_and_exec_input(data, original_stdin));
}
