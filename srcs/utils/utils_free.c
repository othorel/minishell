/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:32 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/07 14:45:06 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_args(t_args *args)
{
	if (!args)
		return ;
	if (args->cmd_param)
	{
		ft_free_tab(&args->cmd_param);
		free(args->cmd_param);
		args->cmd_param = NULL;
	}
	free(args);
	args = NULL;
}

void	ft_free_dollar(t_dollar *dollar)
{
	if (dollar)
	{
		if (dollar->new_str)
			free(dollar->new_str);
		free(dollar);
	}
}

void	ft_free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->args)
		ft_free_args(data->args);
	if (data->input)
		free(data->input);
	if (data->output_file)
		free(data->output_file);
	if (data->input_file)
		free(data->input_file);
	if (data->heredoc_delim)
		free(data->heredoc_delim);
	free(data);
}

void	ft_free_all(t_data *data, char *error, int ex)
{
	if (data)
	{
		if (data->env)
			ft_free_list(&data->env);
		ft_free_data(data);
		if (error)
			ft_print_error(error);
	}
	rl_clear_history();
	if (ex != -1)
		exit(ex);
}
