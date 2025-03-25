/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:45:11 by afontan           #+#    #+#             */
/*   Updated: 2024/11/14 15:08:51 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	sdest;
	size_t	ssrc;

	i = 0;
	sdest = ft_strlen(dest);
	ssrc = ft_strlen(src);
	if (size <= sdest)
		return (size + ssrc);
	while (src[i] && ((sdest + i) < (size - 1)))
	{
		dest[sdest + i] = src[i];
		i++;
	}
	dest[sdest + i] = '\0';
	return (sdest + ssrc);
}
