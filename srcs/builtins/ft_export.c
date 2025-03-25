/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:54:21 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:54:22 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_export_no_args(t_list *env)
{
	char	**tab;
	int		i;
	int		j;

	tab = ft_list_to_tab(env);
	if (!tab)
		return (0);
	ft_sort_list(tab, ft_list_size(env));
	i = 0;
	while (tab[i])
	{
		printf("declare -x ");
		j = 0;
		while (tab[i][j] && tab[i][j] != '=')
			printf("%c", tab[i][j++]);
		if (tab[i][j] && tab[i][j] == '=')
			printf("=\"%s\"\n", &tab[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(tab);
	return (1);
}

static int	ft_check_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=' || str[0] == '%' || str[0] == '\0')
		return (0);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_var_exist(char *str, t_list *env)
{
	int		i;
	int		var;
	t_list	*temp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = 0;
	temp = env;
	if (!ft_strncmp(temp->content, str, i) && (temp->content[i] == '\0'
			|| temp->content[i] == '='))
		return (var);
	temp = temp->next;
	var++;
	while (temp != env)
	{
		if (!ft_strncmp(temp->content, str, i) && (temp->content[i] == '\0'
				|| temp->content[i] == '='))
			return (var);
		temp = temp->next;
		var++;
	}
	return (-1);
}

int	ft_export_var(char *str, t_list **env)
{
	char	*value;
	int		var;
	int		i;

	var = ft_var_exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (0);
	if (var >= 0)
	{
		i = 0;
		while (i < var)
		{
			(*env) = (*env)->next;
			i++;
		}
		free((*env)->content);
		(*env)->content = value;
	}
	else if (var == -1)
	{
		if (!ft_append_node(env, value))
			return (0);
	}
	return (1);
}

int	ft_export(char **str, t_list **env)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (!str || !str[i])
	{
		if (*env && !ft_export_no_args((*env)))
			return (ft_print_error("Error malloc\n"));
		return (0);
	}
	while (str[i])
	{
		if (!ft_check_valid_var(str[i]))
		{
			ft_print_error("minishell: export: `");
			ft_print_error(str[i]);
			ft_print_error("': not a valid identifier\n");
			j = 1;
		}
		else if (!ft_export_var(str[i], env))
			return (ft_print_error("Error malloc\n"));
		i++;
	}
	return (j);
}
