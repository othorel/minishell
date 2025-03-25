/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:28 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:55:29 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_args_size(t_args *list)
{
	t_args	*temp;
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

void	ft_path_abs(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		ft_free_all(data, "malloc error\n", 1);
	if (access(*path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(*path);
		*path = NULL;
	}
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;

	if (str)
		save = str;
	if (!save || !*save)
		return (NULL);
	token = save;
	while (*save && !ft_strchr(delim, *save))
		save++;
	if (*save)
	{
		*save = '\0';
		save++;
	}
	return (token);
}

char	**ft_copy_tab_tab(char **src, int size)
{
	char	**dest;
	int		i;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		if (src[i])
		{
			dest[i] = ft_strdup(src[i]);
			if (!dest[i])
			{
				while (--i >= 0)
					free(dest[i]);
				free(dest);
				return (NULL);
			}
		}
		else
			dest[i] = NULL;
		i++;
	}
	return (dest[size] = NULL, dest);
}

void	ft_reset_tab_no_free(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		tab[i] = NULL;
		i++;
	}
}
