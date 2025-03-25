/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_itoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:49:56 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 11:52:21 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_strrev(char *str, int len)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

static void	ft_zero_and_neg(int *nb, char *str, int *i, int *neg)
{
	if (*nb == 0)
	{
		str[*i] = 48;
		(*i)++;
		str[*i] = '\0';
		return ;
	}
	if (*nb < 0)
	{
		*neg = 1;
		*nb = -(*nb);
	}
}

char	*ft_itoa_static(int nb)
{
	static char	str[255];
	int			i;
	int			neg;

	i = 0;
	neg = 0;
	ft_zero_and_neg(&nb, str, &i, &neg);
	while (nb > 0)
	{
		str[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	ft_strrev(str, i);
	return (str);
}
