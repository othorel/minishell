NAME        = minishell

SRC_DIR     = srcs

OBJ_DIR     = objs

BUILTIN_DIR = $(SRC_DIR)/builtins
EXEC_DIR	= $(SRC_DIR)/exec
UTILS_DIR   = $(SRC_DIR)/utils
PARS_DIR	= $(SRC_DIR)/parsing

SRCS        = $(SRC_DIR)/main.c 			\
			  $(BUILTIN_DIR)/ft_cd.c		\
              $(BUILTIN_DIR)/ft_echo.c  	\
			  $(BUILTIN_DIR)/ft_env.c   	\
              $(BUILTIN_DIR)/ft_exit.c  	\
			  $(BUILTIN_DIR)/ft_export.c	\
              $(BUILTIN_DIR)/ft_pwd.c   	\
			  $(BUILTIN_DIR)/ft_unset.c 	\
			  $(EXEC_DIR)/exec_child.c 		\
			  $(EXEC_DIR)/exec_command.c 	\
			  $(EXEC_DIR)/exec_parent.c 	\
			  $(EXEC_DIR)/exec_pips.c		\
			  $(EXEC_DIR)/exec_redir_pipe.c	\
			  $(EXEC_DIR)/heredoc.c 		\
			  $(EXEC_DIR)/launch_builtin.c  \
			  $(EXEC_DIR)/redirect.c 		\
			  $(UTILS_DIR)/utils_args.c 	\
			  $(UTILS_DIR)/utils_env.c  	\
			  $(UTILS_DIR)/utils_free.c 	\
			  $(UTILS_DIR)/utils_itoa.c 	\
              $(UTILS_DIR)/utils_list.c 	\
              $(UTILS_DIR)/utils_pip.c	 	\
			  $(UTILS_DIR)/utils_signal.c 	\
              $(UTILS_DIR)/utils_str.c 		\
              $(UTILS_DIR)/utils_more.c 	\
			  $(UTILS_DIR)/utils_tab.c 		\
			  $(PARS_DIR)/args_init.c 		\
			  $(PARS_DIR)/count_args.c 		\
			  $(PARS_DIR)/dollar.c 			\
			  $(PARS_DIR)/dollar_utils.c 	\
			  $(PARS_DIR)/env_init.c 		\
			  $(PARS_DIR)/parse_pipe.c 		\
			  $(PARS_DIR)/parse_quote.c 	\
			  $(PARS_DIR)/process_metachar.c 

CC          = gcc
RM          = rm -rf
FLAGS       = -Wall -Werror -Wextra -g3 -I./libft/include -I/usr/include

LIBFT_DR    = libft
LIBFT_A     = $(LIBFT_DR)/libft.a

OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CYAN       = \033[0;32m
BOLD        = \033[1m
RESET       = \033[0m
CYAN		= \033[0;36m
SMILEY      = 👍

all:        $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DR) > /dev/null 2>&1

$(NAME):    $(OBJS) $(LIBFT_A)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_A) -lreadline
	@echo "$(CYAN)$(BOLD)Success: Compilation of $(NAME) complete! $(SMILEY)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@

bonus:      $(LIBFT_A) $(MINILIBX)
	@$(CC) $(FLAGS) -o $(BONUS_NAME) $(LIBFT_A)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DR) clean > /dev/null 2>&1
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)$(BOLD)Success: object files cleaned!$(RESET)"

fclean:     clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DR) fclean > /dev/null 2>&1
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)$(BOLD)Success: Executable $(NAME) removed!$(RESET)"

re:         fclean all

.PHONY:     all clean fclean re bonus