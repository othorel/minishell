/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:10:19 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 10:14:30 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(t_data *data, const char *name)
{
	t_list	*current;
	size_t	name_len;

	current = data->env;
	name_len = ft_strlen(name);
	while (current)
	{
		if (!ft_strncmp(current->content, name, name_len)
			&& current->content[name_len] == '=')
			return (current->content + name_len + 1);
		current = current->next;
	}
	return (NULL);
}

int	ft_replace_env(t_data *data, char *new_var)
{
	t_list	*tmp;
	char	*name;
	size_t	len;

	name = ft_substr(new_var, 0, (size_t)(ft_strchr(new_var, '=') - new_var));
	len = ft_strlen(name);
	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, name, len) == 0
			&& tmp->content[len] == '=')
		{
			free(tmp->content);
			tmp->content = new_var;
			free(name);
			return (1);
		}
		tmp = tmp->next;
	}
	free(name);
	return (ft_append_node(&(data->env), new_var));
}
