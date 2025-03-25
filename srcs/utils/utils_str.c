/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:48 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/07 16:53:22 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_handle_sign_and_whitespace(const char *str, int *i, int *sign)
{
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	return (*i);
}

long long	ft_atoll(const char *str, int *error)
{
	unsigned long long	result;
	int					sign;
	int					i;

	i = 0;
	sign = 1;
	result = 0;
	*error = 0;
	i = ft_handle_sign_and_whitespace(str, &i, &sign);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i++] - '0');
		if (result > (unsigned long long)LONG_MAX && sign == 1)
		{
			*error = 1;
			return (0);
		}
	}
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		*error = 1;
	return ((long long)(result * sign));
}

int	ft_strlen_av(char **av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	return (i);
}

int	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (1);
	return (0);
}

int	ft_print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (1);
}
