USER = $(shell whoami)


L = -L/Users/$(USER)/.brew/opt/readline/lib

I = -I/Users/$(USER)/.brew/opt/readline/include

CC = cc

DBUILD = build

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

HEAD = inc/minishell.h

NAME = minishell

SRCS = garbage_collector/garbage_collector.c main.c parsing/build_tree.c parsing/check_syntax.c parsing/parsing.c \
parsing/tokenize.c printf/ft_printf.c printf/ft_put_u_nbr.c printf/ft_putadress.c printf/ft_putchar.c printf/ft_putnbr.c \
printf/ft_putnbr_base.c printf/ft_putstr.c utils/build_tree/build_list_utils.c utils/build_tree/build_redir_utils.c \
utils/build_tree/build_tree_utils.c utils/build_tree/shunting_utils.c utils/env/env.c utils/env/ft_strdup_env.c utils/ft_strcmp.c \
utils/env/lst_addback_env.c utils/env/lst_array.c utils/env/lstnew_env.c utils/env/lstsize_env.c utils/ft_atoi.c \
utils/ft_isspace.c utils/ft_itoa.c utils/ft_strchr.c utils/ft_strdup_env.c utils/ft_strjoin.c utils/ft_strlcpy.c \
utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strtrim.c utils/tokenize/tokenize_utils.c utils/tokenize/tokenize_utils_1.c \
execution/execute_cmd.c execution/pipe.c execution/redirection_utils.c execution/redirection.c execution/traverse_tree.c \
utils/exit_status.c execution/handle_heredoc.c execution/builtins/export.c

OBJS =  $(addprefix $(DBUILD)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline $(L)

$(DBUILD)/%.o : %.c $(HEAD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(I)

clean :
	rm -rf build

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY : clean
