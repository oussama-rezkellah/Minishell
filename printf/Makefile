# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orezkell <orezkell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/08 04:34:55 by orezkell          #+#    #+#              #
#    Updated: 2023/12/10 04:49:18 by orezkell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
NAME	=	libftprintf.a
SRCS	=	ft_printf.c ft_putchar.c ft_putnbr.c \
			ft_putnbr_base.c ft_putstr.c ft_put_u_nbr.c \
			ft_putadress.c

OBJS	=	${SRCS:%.c=%.o}

CFLAGS	=	-Wall -Wextra -Werror -c

all: $(NAME)

$(NAME) : $(OBJS)
		ar rcs $(NAME) $(OBJS)

%.o : %.c ft_printf.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : clean
