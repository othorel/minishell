/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:36 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:37 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_way_acces(char *dest, char *str, char *env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && i < (4096 - 1))
	{
		dest[i] = env[i];
		i++;
	}
	if (i > 0 && env[i - 1] != '/' && i < (4096 - 1))
		dest[i++] = '/';
	while (str[j] && i < (4096 - 1))
	{
		dest[i++] = str[j++];
	}
	dest[i] = '\0';
	if (i >= 4096 - 1)
	{
		ft_print_error("Path too long\n");
		return (-1);
	}
	return (0);
}

char	*ft_command_not_found(char *str, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_all(data, NULL, 127);
	return (NULL);
}

static char	*ft_check_path(t_list *env, int len)
{
	t_list	*temp;

	temp = env;
	while (len--)
	{
		if (ft_strncmp(temp->content, "PATH=", 5) == 0)
			return (&(temp->content[5]));
		temp = temp->next;
	}
	return (NULL);
}

char	*ft_find_command_path(char *str, t_list *env, t_data *data)
{
	char	*paths;
	char	*token;
	char	*cmd_path;
	char	path[4096];

	paths = ft_check_path(env, ft_list_size(env));
	if (!paths || ft_strlen(str) > 4096 / 2)
		return (ft_command_not_found(str, data));
	token = ft_strtok(paths, ":");
	while (token)
	{
		ft_way_acces(path, str, token);
		if (access(path, F_OK | X_OK) == 0)
		{
			cmd_path = ft_strdup(path);
			if (!cmd_path)
			{
				ft_print_error("Error malloc\n");
				return (NULL);
			}
			return (cmd_path);
		}
		token = ft_strtok(NULL, ":");
	}
	return (ft_command_not_found(str, data));
}

char	*ft_exec_command(t_data *data, char *str, t_list *env)
{
	char	*cmd_path;

	cmd_path = ft_find_command_path(str, env, data);
	if (!cmd_path)
	{
		data->exit_code = -1;
		return (NULL);
	}
	return (cmd_path);
}
