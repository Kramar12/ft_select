# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ariabyi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/04 16:28:42 by ariabyi           #+#    #+#              #
#    Updated: 2018/06/04 18:05:45 by ariabyi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
LIBF = libft/
SRCS = src/
CCFL = -Wall -Wextra -Werror -lncurses -ltermcap -L $(LIBF) -lft

all: $(NAME)

$(NAME):
		@make -C $(LIBF) re
		@gcc $(CCFL) $(SRCS)*.c -o $(NAME)

clean:
		@make -C $(LIBF) clean

fclean:
		@make -C $(LIBF) fclean
		@/bin/rm -rf $(NAME)

re: fclean all
