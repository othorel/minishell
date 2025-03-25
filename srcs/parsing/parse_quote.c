/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:10:47 by afontan           #+#    #+#             */
/*   Updated: 2025/03/10 13:10:52 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	join_prev(char *str, t_data *data, int *i, int *index)
{
	char	*tmp_next;
	int		start;

	start = *i;
	while (str[*i] != '\'' && str[*i] != '"' && str[*i] != ' ' && str[*i])
		(*i)++;
	tmp_next = get_words(str, *i, start);
	data->tmp = ft_strjoin(data->tmp, tmp_next);
	data->args->cmd_param[*index] = ft_strdup(data->tmp);
	free(data->tmp);
	if (data->flag_in_quote == 1 && *index > 0)
	{
		data->tmp = ft_strjoin(data->args->cmd_param[*index - 1],
				data->args->cmd_param[*index]);
		free(data->args->cmd_param[*index]);
		free(data->args->cmd_param[*index - 1]);
		data->args->cmd_param[*index - 1] = ft_strdup(data->tmp);
	}
	else
		(*index)++;
}

static void	join_all(char *str, int *i, int *index, t_data *data)
{
	char	*tmp_prev;

	if (str[*i] && str[*i + 1] && ft_isalpha(str[*i + 1]))
	{
		(*i)++;
		join_prev(str, data, i, index);
	}
	else if (data->flag_in_quote == 1 && *index > 0)
	{
		tmp_prev = ft_strjoin(data->args->cmd_param[*index -1], data->tmp);
		free(data->args->cmd_param[*index -1]);
		data->args->cmd_param[*index -1] = tmp_prev;
		free(data->tmp);
	}
	else
	{
		data->args->cmd_param[*index] = ft_strdup(data->tmp);
		free(data->tmp);
		(*index)++;
		(*i)++;
	}
}

int	is_quote(char *str, t_data *data, int *i, int *index)
{
	int		start;

	if (!str || *i < 0 || !str[*i])
		return (0);
	data->flag_in_quote = 0;
	data->quote = str[*i];
	data->flag_quote = 0;
	if (data->quote == '\'')
		data->flag_quote = 1;
	if (*i > 0 && (ft_isalpha(str[*i - 1]) || str[*i - 1] == '='
			|| str[*i - 1] == '"' || str[*i - 1] == '\''))
		data->flag_in_quote = 1;
	(*i)++;
	start = *i;
	while (str[*i] != data->quote && str[*i])
		(*i)++;
	data->tmp = get_words(str, *i, start);
	join_all(str, i, index, data);
	return (1);
}
