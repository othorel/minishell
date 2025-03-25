/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:08 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 10:49:11 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_variable(char *str, int *i, t_list *env, t_data *data)
{
	char	*var_name;
	char	*value;
	int		start;

	start = *i;
	if (str[*i] == '?')
	{
		var_name = ft_substr(str, *i - 1, 2);
		value = ft_get_special_value(var_name, data);
		*i += 1;
	}
	else if (str[*i] == '$')
	{
		var_name = ft_substr(str, *i - 1, 1);
		value = ft_get_special_value(var_name, data);
		*i += 1;
	}
	else
	{
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		var_name = ft_substr(str, start, *i - start);
		value = ft_get_env_value(var_name, env);
	}
	return (free(var_name), value);
}

int	calculate_new_length(char *str, t_list *env, t_data *data)
{
	int		i;
	int		length;
	char	*value;

	i = 0;
	length = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			value = process_variable(str, &i, env, data);
			if (value)
				length += ft_strlen(value);
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length + 1);
}

char	*ft_expand_dollar(char *str, t_list *env, t_data *data, int index)
{
	t_dollar	dollar;
	char		*value;

	init_dollar(&dollar, str, env, data);
	if (!dollar.new_str)
		return (NULL);
	while (str[dollar.i])
	{
		if (str[dollar.i] == '$')
		{
			dollar.i++;
			value = process_variable(str, &dollar.i, env, data);
			if (value)
			{
				copy_value(&dollar, value);
				value = NULL;
			}
		}
		else
			dollar.new_str[dollar.j++] = str[dollar.i++];
	}
	dollar.new_str[dollar.j] = '\0';
	free(data->args->cmd_param[index]);
	data->args->cmd_param[index] = dollar.new_str;
	return (NULL);
}

void	ft_check_dollar(t_list *env, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->args->cmd_param[i])
	{
		if (data->args->cmd_param[i][0] == '\0')
			i++;
		else
		{
			j = 0;
			while (data->args->cmd_param[i][j])
			{
				if (data->args->cmd_param[i][j] == '$'
					&& data->args->cmd_param[i][j + 1] != '\0'
					&& (data->args->cmd_param[i][j + 1] != '\''))
				{
					ft_expand_dollar(data->args->cmd_param[i], env, data, i);
					break ;
				}
				j++;
			}
			i++;
		}
	}
}
