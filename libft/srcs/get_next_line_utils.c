/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:17:35 by afontan           #+#    #+#             */
/*   Updated: 2025/01/22 09:50:45 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search_newline(t_gnl *store)
{
	int	i;

	if (!store)
		return (0);
	while (store)
	{
		i = 0;
		while (store->content[i] && i < BUFFER_SIZE)
		{
			if (store->content[i] == '\n')
				return (1);
			i++;
		}
		store = store->next;
	}
	return (0);
}

t_gnl	*ft_lstlast_gnl(t_gnl *store)
{
	if (!store)
		return (NULL);
	while (store->next)
		store = store->next;
	return (store);
}

void	cpylst_to_str(t_gnl *store, char *queue)
{
	int	i;
	int	j;

	if (!store)
		return ;
	i = 0;
	while (store)
	{
		j = 0;
		while (store->content[j])
		{
			if (store->content[j] == '\n')
			{
				queue[i++] = '\n';
				queue[i] = '\0';
				return ;
			}
			queue[i++] = store->content[j++];
		}
		store = store->next;
	}
	queue[i] = '\0';
}

int	lstlen_till_newline(t_gnl *store)
{
	int	i;
	int	len;

	if (!store)
		return (0);
	len = 0;
	while (store)
	{
		i = 0;
		while (store->content[i])
		{
			if (store->content[i] == '\n')
				return (len + 1);
			i++;
			len++;
		}
		store = store->next;
	}
	return (len);
}

void	free_store(t_gnl	**store, t_gnl *clean_store, char *product)
{
	t_gnl	*pop_up;

	if (!*store)
		return ;
	while (*store)
	{
		pop_up = (*store)->next;
		free((*store)->content);
		free(*store);
		*store = pop_up;
	}
	*store = NULL;
	if (clean_store->content[0])
		*store = clean_store;
	else
	{
		free(product);
		product = NULL;
		free(clean_store);
		clean_store = NULL;
	}
}
