/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:33 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:34 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_dir(char **path, char *cmd, t_data *data)
{
	struct stat	statbuf;

	stat(*path, &statbuf);
	if (!S_ISREG(statbuf.st_mode))
	{
		ft_print_error("minishell: ");
		ft_print_error(cmd);
		ft_print_error(": Is a directory\n");
		data->exit_code = 126;
		return (0);
	}
	return (1);
}

static int	ft_check_cmd(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = ft_exec_command(data, cmd, data->env);
	else
		ft_path_abs(path, cmd, data);
	if (!(*path) && data->exit_code == -1)
		return (0);
	if (!(*path))
	{
		data->exit_code = 127;
		return (0);
	}
	if (access(*path, X_OK) == -1)
	{
		ft_print_error("minishell: ");
		ft_print_error(cmd);
		ft_print_error(" : command not found\n");
		data->exit_code = 127;
		return (0);
	}
	if (!ft_check_dir(path, cmd, data))
		return (0);
	return (1);
}

static void	ft_redirect(t_data *data, t_args *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next != data->args)
		dup2(pip[1], 1);
	close(pip[1]);
}

void	ft_run_command(t_data *data, t_args *cmd, int *pip, char *path)
{
	char	**env;

	ft_redirect(data, cmd, pip);
	env = ft_list_to_tab(data->env);
	if (env == NULL)
	{
		ft_free_all(data, "malloc eror\n", 1);
		return ;
	}
	if (path == NULL)
	{
		ft_print_error("path is NULL\n");
		data->exit_code = 127;
		ft_free_env(env);
		return ;
	}
	rl_clear_history();
	ft_signals();
	if (execve(path, cmd->cmd_param, env) == -1)
	{
		ft_print_error("execve error\n");
		data->exit_code = 126;
	}
	ft_free_env(env);
}

void	ft_child_process(t_data *data, t_args *cmd, int *pip)
{
	char	*path;

	path = NULL;
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (ft_check_cmd(&path, data, cmd->cmd_param[0]))
		ft_run_command(data, cmd, pip, path);
	if (path != NULL)
		free(path);
}
