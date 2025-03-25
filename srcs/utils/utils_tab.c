/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:52 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:53 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_list_to_tab(t_list *env)
{
	t_list	*list;
	char	**tab;
	int		i;

	tab = NULL;
	i = 0;
	list = env;
	tab = (char **)malloc(sizeof(char *) * (ft_list_size(list) + 1));
	if (!tab)
		return (NULL);
	tab[i] = (list->content);
	list = list->next;
	i++;
	while (list != env)
	{
		tab[i] = (list->content);
		list = list->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

static void	ft_list_swap(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	ft_sort_list(char **tab, int len)
{
	int	i;
	int	j;
	int	cmp;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			cmp = ft_strncmp(tab[i], tab[j], ft_strlen(tab[i] + 1));
			if (cmp > 0)
			{
				ft_list_swap(i, j, tab);
				continue ;
			}
			j++;
		}
		i++;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_count_tab(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}
