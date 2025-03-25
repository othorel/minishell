/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:55:11 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 10:11:07 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_increment_shlvl(t_data *data)
{
	char	*shlvl_value;
	char	*shlvl_str;
	char	*temp;
	int		shlvl;

	shlvl_value = ft_getenv(data, "SHLVL");
	if (shlvl_value)
		shlvl = ft_atoi(shlvl_value) + 1;
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		ft_free_all(data, "Error alloc\n", 1);
	temp = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!temp || !ft_replace_env(data, temp))
		ft_free_all(data, "malloc error\n", 1);
}

int	ft_make_env(t_data *data)
{
	char	path[PATH_MAX];
	char	*temp;

	if (getcwd(path, sizeof(path)) == NULL)
		ft_free_all(data, "getcwd error\n", 1);
	temp = ft_strdup("OLDPWD");
	if (!temp || !ft_append_node(&(data->env), temp))
		ft_free_all(data, "malloc error\n", 1);
	temp = ft_strjoin("PWD=", path);
	if (!temp || !ft_append_node(&(data->env), temp))
		ft_free_all(data, "malloc error\n", 1);
	ft_increment_shlvl(data);
	return (1);
}

int	ft_init_env(t_data *data, char **env)
{
	int		i;
	char	*tmp;
	t_list	*list;

	if (!env || !(*env))
		return (ft_make_env(data));
	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i++]);
		if (!tmp)
			return (0);
		ft_append_node(&list, tmp);
	}
	data->env = list;
	ft_increment_shlvl(data);
	return (1);
}

void	ft_init_data(t_data *data, int ac, char **av)
{
	(void)ac;
	(void)av;
	data->env = NULL;
	data->args = (t_args *)malloc(sizeof(t_args));
	if (!data->args)
		return ;
	ft_memset(data->args, 0, sizeof(t_args));
	data->args->next = data->args;
	data->args->prev = data->args;
	data->args->infile = -1;
	data->args->outfile = -1;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	g_signal_pid = 0;
	ft_signals();
}

void	init_minishell(t_data **data, int ac, char **av, char **env)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		exit(1);
	ft_memset(*data, 0, sizeof(t_data));
	ft_init_data(*data, ac, av);
	ft_init_env(*data, env);
	ft_print_banner();
	(*data)->flag_pipe = 0;
	(*data)->redit_output = 0;
	(*data)->flag_quote = 0;
	(*data)->flag_input = 0;
	(*data)->flag_heredoc = 0;
	(*data)->input_file = NULL;
	(*data)->output_file = NULL;
	(*data)->heredoc_delim = NULL;
	(*data)->tmp = NULL;
	(*data)->redit_output = 0;
	(*data)->input = NULL;
	(*data)->exit_code = 0;
}
