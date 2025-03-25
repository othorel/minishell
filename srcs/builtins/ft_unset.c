/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:30 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:31 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_id_syntax(char *str)
{
	int	i;

	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_id_exist(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*temp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	j = 0;
	temp = env;
	if (!ft_strncmp(temp->content, str, i))
		return (j);
	temp = temp->next;
	j++;
	while (temp != env)
	{
		if (!ft_strncmp(temp->content, str, i))
			return (j);
		temp = temp->next;
		j++;
	}
	return (-1);
}

static void	ft_check_unset(t_list *temp, t_list **env)
{
	if (temp == (*env))
		(*env) = temp->next;
	if (temp->next == temp)
		(*env) = NULL;
}

static int	ft_verif_unset(char *str, t_list **env)
{
	int		pos;
	int		i;
	t_list	*temp;

	if (!str || !(*str))
		return (0);
	if (!ft_id_syntax(str))
	{
		ft_print_error("unset: invalid identifier\n");
		return (1);
	}
	pos = ft_id_exist(str, (*env));
	if (pos == -1)
		return (0);
	temp = (*env);
	i = 0;
	while (i++ < pos)
		temp = temp->next;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	free(temp->content);
	ft_check_unset(temp, env);
	free(temp);
	temp = NULL;
	return (0);
}

int	ft_unset(char **str, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (str[i])
	{
		if (ft_verif_unset(str[i], env))
		{
			exit_code = 1;
			break ;
		}
		i++;
	}
	return (exit_code);
}
