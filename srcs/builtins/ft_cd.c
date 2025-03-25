/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:53:53 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/05 13:53:54 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	old_pwd(t_data *data)
{
	t_list	*temp;
	char	*str;
	int		len;

	temp = data->env;
	str = NULL;
	len = ft_list_size(temp);
	while (len--)
	{
		if (ft_strncmp(temp->content, "PWD=", 4) == 0)
			str = temp->content;
		temp = temp->next;
	}
	if (!str)
		ft_export_var("OLDPWD", &data->env);
	if (str)
	{
		str = ft_strjoin("OLD", str);
		if (!str)
			return (ft_print_error("Error malloc\n"));
		ft_export_var(str, &data->env);
	}
	free(str);
	return (1);
}

static void	new_pwd(t_data *data, char *av)
{
	char	cwd[4096];
	char	*pwd;

	old_pwd(data);
	if (getcwd(cwd, 4096) == NULL)
	{
		perror(av);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return ;
	ft_export_var(pwd, &data->env);
	free(pwd);
}

int	ft_cd(t_data *data, char **av)
{
	int	str;

	if (ft_strlen_av(av) == 2)
	{
		str = chdir(av[1]);
		if (str == 0)
			new_pwd(data, av[1]);
		if (str == -1)
			str *= -1;
		if (str == 1)
			perror(av[1]);
		return (str);
	}
	return (1);
}
