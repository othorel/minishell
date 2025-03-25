/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_metachar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:24 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:25 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_trunc_and_append(char *str, t_data *data, int *i, int *index)
{
	int		start;
	char	*filename;

	(*i)++;
	if (str[*i] == '>')
	{
		(*i)++;
		data->redit_output = 2;
	}
	else
		data->redit_output = 1;
	while (str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && !ft_meta_char(str[*i]))
		(*i)++;
	filename = get_words(str, *i, start);
	index++;
	data->output_file = filename;
}

void	process_input(char *str, t_data *data, int *i, int *index)
{
	int		start;
	char	*filename;

	(*i)++;
	data->flag_heredoc = 1;
	while (str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && !ft_meta_char(str[*i]))
		(*i)++;
	filename = get_words(str, *i, start);
	index++;
	data->heredoc_delim = filename;
}

void	process_heredoc(char *str, t_data *data, int *i, int *index)
{
	int		start;
	char	*filename;

	while (str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && !ft_meta_char(str[*i]))
		(*i)++;
	filename = get_words(str, *i, start);
	index++;
	data->input_file = filename;
	data->flag_input = 1;
}

void	process_metachar(char *str, t_data *data, int *i, int *index)
{
	if (str[*i] == '>')
		process_trunc_and_append(str, data, i, index);
	else if (str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '<')
			process_input(str, data, i, index);
		else
			process_heredoc(str, data, i, index);
	}
}
