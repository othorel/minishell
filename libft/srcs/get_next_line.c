/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:31:35 by afontan           #+#    #+#             */
/*   Updated: 2025/01/22 15:30:22 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_gnl	*store[200000];
	t_gnl			*error;
	char			*queue;

	if (fd < 0 || fd > 200000 || BUFFER_SIZE <= 0)
		return (NULL);
	queue = NULL;
	if (inventory(store, fd) == -1)
	{
		while (store[fd])
		{
			error = store[fd]->next;
			free(store[fd]->content);
			free(store[fd]);
			store[fd] = error;
		}
		store[fd] = NULL;
	}
	if (!store[fd])
		return (NULL);
	queue = fetch_queue(store[fd]);
	cutting_in(&store[fd]);
	return (queue);
}

int	inventory(t_gnl **store, int fd)
{
	int		bill;
	char	*product;

	bill = 0;
	while (!search_newline(store[fd]))
	{
		product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!product)
			return (bill);
		bill = read(fd, product, BUFFER_SIZE);
		if (bill <= 0)
		{
			free(product);
			product = NULL;
			return (bill);
		}
		product[bill] = '\0';
		stock_replenishment(store, product, fd);
	}
	return (bill);
}

void	stock_replenishment(t_gnl **store, char *product, int fd)
{
	t_gnl	*new_product;
	t_gnl	*last_product;

	last_product = ft_lstlast_gnl(store[fd]);
	new_product = (t_gnl *)malloc(sizeof(t_gnl));
	if (!new_product)
		return ;
	if (!last_product)
		store[fd] = new_product;
	else
		last_product->next = new_product;
	new_product->content = product;
	new_product->next = NULL;
}

char	*fetch_queue(t_gnl *store)
{
	int		queue_len;
	char	*next_queue;

	if (!store)
		return (NULL);
	queue_len = lstlen_till_newline(store);
	next_queue = (char *)ft_calloc(1, sizeof(char) * (queue_len + 1));
	if (!next_queue)
		return (NULL);
	cpylst_to_str(store, next_queue);
	return (next_queue);
}

void	cutting_in(t_gnl **store)
{
	t_gnl	*last_product;
	t_gnl	*clean_store;
	int		i;
	int		j;
	char	*product;

	product = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	clean_store = (t_gnl *)malloc(sizeof(t_gnl));
	if (!product || !clean_store)
		return ;
	last_product = ft_lstlast_gnl(*store);
	i = 0;
	j = 0;
	while (last_product->content[i] && last_product->content[i] != '\n')
		i++;
	while (last_product->content[i] && last_product->content[++i])
		product[j++] = last_product->content[i];
	product[j] = '\0';
	clean_store->content = product;
	clean_store->next = NULL;
	free_store(store, clean_store, product);
}

/* 

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char *str;
	//ssize_t rd_file;

	int fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	 	perror("Erreur lors de l'ouverture");
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	//get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);

	str = get_next_line(fd);
	printf("%s", str);
	free (str);
	str = NULL;
	close(fd);
}  */