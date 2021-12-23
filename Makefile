# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 11:33:44 by tkirihar          #+#    #+#              #
#    Updated: 2021/12/23 18:34:45 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = 		libmem_mgt.a

SRCS = 		mem_mgt.c

OBJS = 		$(SRCS:.c=.o)

CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Wextra -Werror

$(NAME):	$(OBJS)
			ar rcs $@ $^

all:		$(NAME)

.c.o:
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
