/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:52:20 by olthorel          #+#    #+#             */
/*   Updated: 2025/03/10 11:52:41 by olthorel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

extern pid_t	g_signal_pid;

typedef struct s_args
{
	int				skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_args	*next;
	struct s_args	*prev;
}					t_args;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_dollar
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;
}			t_dollar;

typedef struct s_pipex
{
	int		i;
	int		fd[2];
	int		in_fd;
	pid_t	pid;
}			t_pipex;

typedef struct s_data
{
	t_list		*env;
	t_args		*args;
	char		*input;
	int			redit_output;
	int			flag_in_quote;
	char		*output_file;
	char		*input_file;
	char		*heredoc_delim;
	char		*tmp;
	char		quote;
	int			flag_input;
	int			flag_quote;
	int			flag_pipe;
	int			flag_heredoc;
	int			exit_code;
	int			pipe_fd[2];
}				t_data;

/* ************************************************************************** */
/*                             UTILS ARGS                                     */
/* ************************************************************************** */

void		ft_path_abs(char **path, char *cmd, t_data *data);
void		ft_reset_tab_no_free(char **tab);
char		*ft_strtok(char *str, const char *delim);
char		**ft_copy_tab_tab(char **src, int size);
size_t		ft_args_size(t_args *list);

/* ************************************************************************** */
/*                             UTILS ENV                                      */
/* ************************************************************************** */

char		*ft_getenv(t_data *data, const char *name);
int			ft_replace_env(t_data *data, char *new_var);

/* ************************************************************************** */
/*                             UTILS FREE                                     */
/* ************************************************************************** */

void		ft_free_tab(char ***av);
void		ft_free_all(t_data *data, char *error, int ex);
void		ft_free_data(t_data *data);
void		ft_free_args(t_args *args);
void		ft_free_env(char **env);
void		ft_free_dollar(t_dollar *dollar);
void		free_data_pipe(t_data **data_pipe);
int			ft_free_list(t_list **list);

/* ************************************************************************** */
/*                             UTILS ITOA                                     */
/* ************************************************************************** */

char		*ft_itoa_static(int nb);

/* ************************************************************************** */
/*                             UTILS LIST                                     */
/* ************************************************************************** */

void		ft_print_banner(void);
int			ft_append_node(t_list **list, char *new_elem);
size_t		ft_list_size(t_list *list);

/* ************************************************************************** */
/*                             UTILS SIGNAL                                   */
/* ************************************************************************** */

void		ft_clear_line(void);
void		handle_heredoc_sigint(int sign);
void		ft_signals(void);

/* ************************************************************************** */
/*                             UTILS STR                                      */
/* ************************************************************************** */

long long	ft_atoll(const char *str, int *error);
int			ft_strlen_av(char **av);
int			is_space(char c);
int			ft_print_error(char *str);

/* ************************************************************************** */
/*                             UTILS TAB                                      */
/* ************************************************************************** */

void		ft_sort_list(char **tab, int len);
void		ft_init_data_pipe(t_data *data);
char		**ft_list_to_tab(t_list *env);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_count_tab(char **str);

/* ************************************************************************** */
/*                             UTILS MORE                                     */
/* ************************************************************************** */

int			empty_line(char *line);
void		reset_flags(t_data *data);
void		free_pipe_data(t_data **data_pipe);
char		*ft_getenv(t_data *data, const char *name);


/* ************************************************************************** */
/*                             BUILTINS                                       */
/* ************************************************************************** */

void		ft_exit(t_data *data, char **av, int error);
int			ft_cd(t_data *data, char **av);
int			ft_echo(char **args);
int			ft_env(t_list *list);
int			ft_export_var(char *str, t_list **env);
int			ft_export(char **args, t_list **env);
int			ft_pwd(void);
int			ft_unset(char **str, t_list **env);

/* ************************************************************************** */
/*                             PARSING                                        */
/* ************************************************************************** */

int			ft_split_input(char *str, t_data *data, int *index);
int			check_first_pip(t_data *data);
int			ft_count_args(char *str);
int			execute_with_redirection(t_data *data);
int			redirect_output(t_data *data, int append);
int			ft_init_env(t_data *data, char **env);
int			ft_meta_char(int c);
int			count_pipes(const char *input);
int			is_quote(char *str, t_data *data, int *i, int *index);
int			calculate_new_length(char *str, t_list *env, t_data *data);
void		init_minishell(t_data **data, int ac, char **av, char **env);
void		ft_init_data(t_data *data, int ac, char **av);
void		ft_check_dollar(t_list *env, t_data *data);
void		process_trunc_and_append(char *str, t_data *data,
				int *i, int *index);
void		process_input(char *str, t_data *data, int *i, int *index);
void		process_heredoc(char *str, t_data *data, int *i, int *index);
void		process_pipe(char *str, t_data *data, int *i, int *index);
void		process_metachar(char *str, t_data *data, int *i, int *index);
void		init_dollar(t_dollar *dollar, char *str, t_list *env, t_data *data);
void		copy_value(t_dollar *dollar, char *value);
char		*get_words(char *str, int i, int start);
char		*ft_expand_dollar(char *str, t_list *env, t_data *data, int index);
char		**allocate_strs(int count);
char		*ft_get_special_value(char *var, t_data *data);
char		*ft_get_env_value(char *var, t_list *env);

/* ************************************************************************** */
/*                             EXEC                                           */
/* ************************************************************************** */

int			ft_is_builtin(char *cmd);
int			ft_exec(t_data *data);
int			execute_pipeline(t_data *data, t_data **data_pipe);
int			execute_with_redirection(t_data *data);
int			heredoc(const char *delimiter, t_data *data);
int			redirect_input(t_data *data);
int			redirect_output(t_data *data, int append);
int			ft_way_acces(char *dest, char *str, char *env);
int			empty_line(char *line);
int			check_next_pipe(t_data **data_pipe, int i, int *fd);
int			ft_exec_process(t_data *data, t_args *cmd, int *pip);
int			redirect_input(t_data *data);
int			ft_open_and_redirect_input(t_data *data);
void		apply_redirection(t_data *data);
void		ft_run_command(t_data *data, t_args *cmd, int *pip, char *path);
void		ft_child_process(t_data *data, t_args *cmd, int *pip);
void		ft_exec_pip(t_data *data);
void		ft_wait_process(t_data *data);
void		ft_exec_builtin(int stdout, t_data *data, t_args *cmd);
char		*ft_exec_command(t_data *data, char *str, t_list *env);
char		*ft_find_command_path(char *str, t_list *env, t_data *data);
char		*ft_strtok_pipe(char *str, const char *delim);
char		*ft_command_not_found(char *str, t_data *data);
t_data		**ft_split_pip(t_data *data);
t_data		**pars_arg_pipe(t_data *data);
t_data		**copy_in_pipe(t_data *data, int count);

#endif