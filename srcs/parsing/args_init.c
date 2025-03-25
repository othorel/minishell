/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:11:05 by afontan           #+#    #+#             */
/*   Updated: 2025/03/10 13:11:14 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_meta_char(int c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*get_words(char *str, int i, int start)
{
	int		len;
	char	*dest;

	len = i - start;
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str + start, len + 1);
	return (dest);
}

static int	skip_whitespace(char *str, t_data *data, int *i, int *index)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (str[*i] == '\0')
		return (0);
	if (str[*i] == '"' || str[*i] == '\'')
	{
		is_quote(str, data, i, index);
		return (1);
	}
	return (1);
}

static int	collect_args(char *str, t_data *data, int *index, int start)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!skip_whitespace(str, data, &i, index))
			break ;
		start = i;
		if (ft_meta_char(str[i]))
			process_metachar(str, data, &i, index);
		else if (str[i] && str[i] != ' ' && !ft_meta_char(str[i])
			&& str[i] != '\t' && str[i] != '\'' && str[i] != '"'
			&& str[i] != '=')
		{
			while (str[i] && str[i] != ' ' && str[i] != '\t'
				&& !ft_meta_char(str[i]) && str[i] != '\'' && str[i] != '"')
				i++;
			data->args->cmd_param[*index] = get_words(str, i, start);
			(*index)++;
		}
	}
	return (1);
}

int	ft_split_input(char *str, t_data *data, int *index)
{
	int	count;

	count = ft_count_args(str);
	if (count == 0)
		return (0);
	if (count == -1)
	{
		ft_free_tab(&data->args->cmd_param);
		return (ft_print_error ("minishell: syntax error near unexpected \
token\n"), 0);
	}
	data->args->cmd_param = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!data->args->cmd_param)
		return (0);
	if (!collect_args(str, data, index, 0))
	{
		ft_free_tab(&data->args->cmd_param);
		return (0);
	}
	data->args->cmd_param[*index] = NULL;
	if (!execute_with_redirection(data))
		return (ft_free_tab(&data->args->cmd_param), 0);
	return (1);
}
