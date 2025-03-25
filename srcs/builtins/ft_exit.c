/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:12 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:16 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data *data, char **av, int error)
{
	long long	result;

	result = 0;
	ft_putstr_fd("exit\n", 2);
	if (av[1])
	{
		result = ft_atoll(av[1], &error);
		if (error)
		{
			ft_print_error("minishell: exit: ");
			ft_print_error(av[1]);
			ft_print_error(": numeric argument required\n");
			ft_free_all(data, NULL, 255);
		}
	}
	if (av[1] && av[2])
	{
		ft_print_error("minishell: exit: too many arguments\n");
		data->exit_code = 1;
		ft_free_all(data, NULL, data->exit_code);
		return ;
	}
	ft_free_all(data, NULL, (unsigned char)result);
}
