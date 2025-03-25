/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:41 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:42 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_first_pip(t_data *data)
{
	if (data->input[0] == '|')
	{
		if (data->input[1] == '|')
		{
			ft_print_error("minishell: syntax error near \
unexpected token `||'\n");
			return (0);
		}
		else
		{
			ft_print_error("minishell: syntax error near \
unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

static void	handle_quotes(char **next_tk, int *in_quote, char *quote_char)
{
	if (**next_tk == '"' || **next_tk == '\'')
	{
		if (!*in_quote)
		{
			*in_quote = 1;
			*quote_char = **next_tk;
		}
		else if (**next_tk == *quote_char)
		{
			*in_quote = 0;
		}
	}
}

char	*ft_strtok_pipe(char *str, const char *delim)
{
	static char	*next_token = NULL;
	char		*start;
	int			in_quote;
	char		quote_char;

	in_quote = 0;
	quote_char = '\0';
	if (str)
		next_token = str;
	if (!next_token || *next_token == '\0')
		return (NULL);
	start = next_token;
	while (*next_token)
	{
		handle_quotes(&next_token, &in_quote, &quote_char);
		if (!in_quote && delim && ft_strchr(delim, *next_token))
		{
			*next_token = '\0';
			next_token++;
			break ;
		}
		next_token++;
	}
	return (start);
}

void	free_data_pipe(t_data **data_pipe)
{
	int	i;

	i = 0;
	while (data_pipe[i] != NULL)
	{
		ft_free_data(data_pipe[i]);
		i++;
	}
	free(data_pipe);
}
