# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/01 09:16:47 by mizola            #+#    #+#              #
#    Updated: 2020/10/01 09:16:48 by mizola           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	minishell.c ft_pwd.c ft_launch.c ft_cd.c ft_env.c \
		ft_data_init.c ft_identlstback.c ft_redlstback.c \
		ft_redirect.c ft_export.c ft_echo.c ft_red_array.c ft_dir.c \
		ft_cmd.c ft_exit.c ft_unset.c ft_gnl.c ft_split_quote.c \
		parse/ft_parse.c parse/ft_skip_space.c parse/ft_get_len_str_cmd.c \
		parse/ft_check_cmd.c parse/ft_is_red.c parse/ft_strdup_env_val.c \
		parse/ft_is_valid_cmd.c parse/ft_valid_str.c \
		parse/ft_get_red_val_init.c parse/ft_skip_back_n.c \
		ft_env_utils.c ft_file.c ft_redirect_utils.c \
		ft_fork_pipe.c ft_fork_pipe_utils.c ft_env_value.c ft_export_utils.c \
		ft_free_xxx.c parse/ft_valid_arr_str.c ft_check_exec.c ft_red_new.c \

FLAGS = -Wall -Wextra -Werror

OSRC = $(SRC:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OSRC)
	make -C ./libft
	gcc $(FLAGS) $(OSRC) -L libft -lft -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf  $(OSRC)
	make -C ./libft clean

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

n:
	norminette *.c *.h parse/*.c parse/*.h libft/*.c libft/*.h

s:
	wc *.c *.h parse/*

.PHONY: all clean fclean re n s
