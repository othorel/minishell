/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:45 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:46 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_sigint(int sign)
{
	(void)sign;
	printf("\n");
	ft_clear_line();
	if (g_signal_pid == 0)
		rl_redisplay();
}

void	ft_clear_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_heredoc_sigint(int sign)
{
	(void)sign;
	g_signal_pid = 1;
	exit (1);
}

void	ft_signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
