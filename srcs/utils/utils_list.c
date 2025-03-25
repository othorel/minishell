/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:35 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:36 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_list_new(t_list **new, char *new_elem)
{
	(*new) = malloc(sizeof(t_list));
	if (!(*new))
		return (0);
	(*new)->content = new_elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

static void	ft_add_front(t_list **list, t_list *new_elem)
{
	(*list) = new_elem;
	(*list)->prev = *list;
	(*list)->next = *list;
}

size_t	ft_list_size(t_list *list)
{
	t_list	*temp;
	size_t	i;

	if ((list))
	{
		temp = list;
		i = 1;
		while (temp->next != list)
		{
			i++;
			temp = temp->next;
		}
		return (i);
	}
	return (0);
}

int	ft_append_node(t_list **list, char *new_elem)
{
	t_list	*new;

	if (!ft_list_new(&new, new_elem))
		return (0);
	if (!(*list))
		ft_add_front(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

void	ft_print_banner(void)
{
	printf("\033[1;36m");
	printf("==============================================================\n");
	printf("\n"
		" ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\n"
		" ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\n"
		" ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\n"
		" ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\n"
		" ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"
		" ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		);
	printf("==============================================================\n");
	printf("    	 🚀 Minishell by olthorel and afontan 🚀\n");
	printf("==============================================================\n");
	printf("\033[0m");
}
