/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:56 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 13:17:33 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	g_signal_pid;

int	ft_check_pipe(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			if (input[i + 1] == '\0')
				return (0);
			i++;
			while ((input[i] != quote) && input[i])
				i++;
		}
		if (input[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	handle_pipeline(t_data *data)
{
	t_data	**data_pipe;

	if (!check_first_pip(data))
		return ;
	if (count_pipes(data->input))
	{
		data_pipe = ft_split_pip(data);
		execute_pipeline(data, data_pipe);
	}
}

void	handle_single_command(t_data *data, int *argc)
{
	if (ft_split_input(data->input, data, argc))
	{
		if (data->redit_output == 0 && data->flag_input == 0
			&& data->flag_heredoc == 0 && data->flag_pipe == 0)
		{
			if (!ft_exec(data))
				ft_putstr_fd("command not found\n", 2);
		}
	}
	ft_free_tab(&data->args->cmd_param);
}

void	process_main(t_data *data)
{
	int	argc;

	argc = 0;
	if (!data->input || empty_line(data->input))
		return ;
	add_history(data->input);
	if (ft_check_pipe(data->input))
	{
		handle_pipeline(data);
	}
	else
	{
		handle_single_command(data, &argc);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	init_minishell(&data, ac, av, env);
	while (1)
	{
		data->input = readline("minishell> ");
		if (!data->input)
		{
			ft_free_all(data, "exit\n", data->exit_code);
			break ;
		}
		process_main(data);
		reset_flags(data);
		free(data->input);
	}
	rl_clear_history();
	ft_free_all(data, NULL, -1);
	return (0);
}
