/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:12:58 by afontan           #+#    #+#             */
/*   Updated: 2024/11/15 10:25:51 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_c(const char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len_str;
	int		i;
	int		j;

	i = 0;
	len_str = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && check_c(set, s1[i]) == 1)
		i++;
	while (j >= i && check_c(set, s1[j]) == 1)
		j--;
	str = malloc(j - i + 2);
	if (str == NULL)
		return (NULL);
	while (i < j + 1)
		str[len_str++] = s1[i++];
	str[len_str] = '\0';
	return (str);
}
