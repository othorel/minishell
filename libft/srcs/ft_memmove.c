/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:04:07 by afontan           #+#    #+#             */
/*   Updated: 2024/11/14 15:11:01 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tmp;
	char	*dest;

	if (dst == NULL && src == NULL)
		return (NULL);
	tmp = (char *)src;
	dest = (char *)dst;
	i = 0;
	if (tmp < dest)
	{
		while (n-- > 0)
		{
			dest[n] = tmp[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest[i] = tmp [i];
			i++;
		}
	}
	return (dst);
}
