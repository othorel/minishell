/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:38 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 10:09:45 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
		return (1);
	return (0);
}

void	reset_flags(t_data *data)
{
	data->flag_pipe = 0;
	data->redit_output = 0;
	data->flag_input = 0;
	data->flag_heredoc = 0;
	g_signal_pid = 0;
}

void	ft_free_tab(char ***av)
{
	int	i;

	if (!av || !(*av))
		return ;
	i = 0;
	while ((*av)[i])
	{
		free((*av)[i]);
		(*av)[i] = NULL;
		i++;
	}
	free(*av);
	*av = NULL;
}

int	ft_free_list(t_list **list)
{
	t_list	*temp;
	t_list	*cur;

	if (!(*list))
		return (0);
	cur = *list;
	while (cur->next != *list)
	{
		temp = cur;
		cur = cur->next;
		free(temp->content);
		free(temp);
	}
	free(cur->content);
	free(cur);
	*list = NULL;
	return (0);
}

void	free_pipe_data(t_data **data_pipe)
{
	int	i;

	i = 0;
	while (data_pipe[i])
	{
		if (data_pipe[i]->input_file)
			free(data_pipe[i]->input_file);
		if (data_pipe[i]->output_file)
			free(data_pipe[i]->output_file);
		if (data_pipe[i]->args)
			ft_free_args(data_pipe[i]->args);
		free(data_pipe[i]);
		i++;
	}
	if (data_pipe)
		free(data_pipe);
}
