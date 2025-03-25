/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:07 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:08 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_list *list)
{
	t_list	*temp;

	temp = list;
	if (!temp)
		return (0);
	if (ft_strchr(temp->content, '='))
		printf("%s\n", temp->content);
	temp = temp->next;
	while (temp != list)
	{
		if (ft_strchr(temp->content, '='))
			printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}
