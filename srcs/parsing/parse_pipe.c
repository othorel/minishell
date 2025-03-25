/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:15 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 10:20:55 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(const char *input)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	ft_free_data_pipe(t_data **data_pipe, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data_pipe[i])
		{
			ft_free_data(data_pipe[i]);
		}
		i++;
	}
	free(data_pipe);
}

void	init_data_pipe(t_data **data_pipe, int i)
{
	data_pipe[i] = malloc(sizeof(t_data));
	if (!data_pipe[i])
		return ;
	ft_memset(data_pipe[i], 0, sizeof(t_data));
	data_pipe[i]->args = malloc(sizeof(t_args));
	if (!data_pipe[i]->args)
		return ;
	ft_memset(data_pipe[i]->args, 0, sizeof(t_args));
}

static t_data	**ft_zeub_pipes(t_data *data, int count)
{
	int			i;
	char		*pip;
	int			argc;
	char		*str;
	t_data		**data_pipe;

	i = 0;
	data_pipe = malloc((count + 2) * sizeof(t_data *));
	pip = ft_strtok_pipe(data->input, "|");
	while (pip)
	{
		str = ft_strdup(pip);
		if (!str)
			return (ft_free_data_pipe(data_pipe, i), NULL);
		pip = ft_strtok_pipe(NULL, "|");
		argc = 0;
		init_data_pipe(data_pipe, i);
		data_pipe[i]->flag_pipe = 1;
		ft_split_input(str, data_pipe[i], &argc);
		free(str);
		i++;
	}
	data_pipe[i] = NULL;
	return (data_pipe);
}

t_data	**ft_split_pip(t_data *data)
{
	int		count;

	count = count_pipes(data->input);
	return (ft_zeub_pipes(data, count));
}
