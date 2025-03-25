/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:05 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 11:50:18 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_env_value(char *var, t_list *env)
{
	t_list	*start;

	start = env;
	while (env)
	{
		if (ft_strncmp(env->content, var, ft_strlen(var)) == 0
			&& env->content[ft_strlen(var)] == '=')
			return (env->content + ft_strlen(var) + 1);
		env = env->next;
		if (env == start)
			break ;
	}
	return (NULL);
}

char	*ft_get_special_value(char *var, t_data *data)
{
	if (ft_strncmp(var, "?", 1) == 0)
		return (ft_itoa_static(data->exit_code));
	if (ft_strncmp(var, "$", 1) == 0 && ft_strncmp(var, "$?", 2) == 0)
		return (ft_itoa_static(data->exit_code));
	if (ft_strncmp(var, "$", 1) == 0)
		return (ft_itoa_static(getpid()));
	return (NULL);
}

void	init_dollar(t_dollar *dollar, char *str, t_list *env, t_data *data)
{
	if (!dollar)
	{
		dollar = (t_dollar *)malloc(sizeof(t_dollar));
		if (!dollar)
			return ;
	}
	dollar->i = 0;
	dollar->j = 0;
	dollar->new_len = calculate_new_length(str, env, data);
	dollar->new_str = (char *)malloc(dollar->new_len + 1);
	if (!dollar->new_str)
	{
		ft_free_dollar(dollar);
		return ;
	}
	dollar->new_str[0] = '\0';
}

void	copy_value(t_dollar *dollar, char *value)
{
	int	part_len;

	part_len = ft_strlen(value);
	ft_memcpy(&dollar->new_str[dollar->j], value, part_len);
	dollar->j += part_len;
}
