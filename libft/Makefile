# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/11 14:02:02 by mizola            #+#    #+#              #
#    Updated: 2020/05/16 18:11:07 by mizola           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_MAIN =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_strtrim_free.c ft_strjoin_free.c ft_strlen_null.c ft_arrstrjoin.c \
		ft_arrstrlen.c ft_arrstrlen_null.c ft_atoi_shell.c ft_free_arrstr.c \
		ft_error.c

SRC_BONUS =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	 	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c

OSRC_MAIN = $(SRC_MAIN:.c=.o)

OSRC_BONUS = $(SRC_BONUS:.c=.o)

HEADER = libft.h

FLAGS = -Wall -Wextra -Werror -c -std=c99

all: $(NAME) $(OSRC_MAIN) $(OSRC_BONUS)

$(NAME): $(SRC_MAIN) $(SRC_BONUS) $(HEADER)
	@gcc $(FLAGS) $(SRC_MAIN) $(SRC_BONUS)
	@ar rc $(NAME) $(OSRC_MAIN) $(OSRC_BONUS)
	@ranlib $(NAME)

bonus: $(OSRC_BONUS)

$(OSRC_BONUS): $(SRC_BONUS) $(HEADER)
	@gcc $(FLAGS) $(SRC_BONUS)
	@ar rc $(NAME) $(OSRC_BONUS)
	@ranlib $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OSRC_MAIN) $(OSRC_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
