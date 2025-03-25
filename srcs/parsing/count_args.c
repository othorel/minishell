/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:09:07 by afontan           #+#    #+#             */
/*   Updated: 2025/03/10 13:12:21 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_quote(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		(*i)++;
		if (str[*i] && str[*i] == quote && str[*i + 1]
			&& (str[*i + 1] == '\'' || str[*i + 1] == '"'))
		{
			(*i)++;
			quote = str[*i];
			(*i)++;
		}
	}
	if (str[*i] == '\0')
		return (0);
	(*i)++;
	return (1);
}

int	ft_count_tools(char *str, int *i)
{
	if (str[*i] == '\'' || str[*i] == '"')
	{
		if (!count_quote(str, i))
			return (0);
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '"')
			(*i)++;
	}
	else if (ft_meta_char(str[*i]))
	{
		if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == str[*i])
		{
			if (str[*i + 2] == str[*i])
				return (0);
			(*i) += 2;
		}
		else
			(*i)++;
	}
	else
		while (str[*i] != ' ' && str[*i] != '\0' && !ft_meta_char(str[*i])
			&& str[*i] != '\'' && str[*i] != '"')
			(*i)++;
	return (1);
}

int	ft_count_args(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		if (!ft_count_tools(str, &i))
			return (-1);
		count++;
	}
	return (count);
}
