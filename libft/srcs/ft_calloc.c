/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:38:18 by afontan           #+#    #+#             */
/*   Updated: 2024/12/12 13:14:52 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitem, size_t size)
{
	void	*ptr;
	size_t	sizetotal;

	sizetotal = nitem * size;
	if (nitem != 0 && sizetotal / nitem != size)
		return (NULL);
	ptr = (void *)malloc(sizetotal);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nitem * size);
	return (ptr);
}
