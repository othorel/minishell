# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olthorel <olthorel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 10:01:47 by afontan           #+#    #+#              #
#    Updated: 2025/01/28 18:18:45 by olthorel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = libft.a

OBJ_DIR         = objs
SRC_DIR         = srcs
INCLUDE_DIR     = include
PRINTF_DIR      = ft_printf

SRCS            = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				 ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
				 ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
				 ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				 ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
				 ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
				 ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
				 ft_memcmp.c get_next_line.c get_next_line_utils.c 

PRINTF_SRCS     = $(addprefix $(PRINTF_DIR)/, ft_printf.c ft_toolspf.c ft_putnbr_dif.c)

SRCS_ALL        = $(SRCS) $(PRINTF_SRCS)

OBJ_FILES       = $(addprefix $(OBJ_DIR)/, $(SRCS_ALL:.c=.o))

CC              = gcc
RM              = rm -f
FLAGS           = -Wall -Werror -Wextra -I$(INCLUDE_DIR)

all:            ${NAME}

${NAME} :       ${OBJ_FILES}
				@ar rcs ${NAME} ${OBJ_FILES}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/$(PRINTF_DIR)/%.o: $(PRINTF_DIR)/%.c
				@mkdir -p $(OBJ_DIR)/$(PRINTF_DIR)
				@$(CC) $(FLAGS) -c $< -o $@
clean:  
				@${RM} ${OBJ_FILES}

fclean:         clean
				@${RM} ${NAME}

re:             fclean all

.PHONY:         all clean fclean re
