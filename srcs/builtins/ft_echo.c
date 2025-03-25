/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:53:58 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:53:59 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_n(char *str)
{
	int	i;

	if (!str || str[0] != '-' || ft_strlen(str) < 2)
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

static void	ft_write_echo(int count, int i, int *flag_line, char **av)
{
	while (i < count && ft_check_n(av[i]))
	{
		*flag_line = 0;
		i++;
	}
	while (i < count)
	{
		if (av[i])
		{
			write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		}
		if (i != (count - 1))
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (*flag_line)
		write(1, "\n", 1);
}

int	ft_echo(char **args)
{
	int	i;
	int	count;
	int	flag_line;

	if (!args || !args[0])
		return (0);
	count = 0;
	while (args[count])
		count++;
	i = 1;
	flag_line = 1;
	ft_write_echo(count, i, &flag_line, args);
	return (0);
}
