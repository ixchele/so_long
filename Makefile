# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 16:17:43 by zbengued          #+#    #+#              #
#    Updated: 2025/02/23 16:16:53 by zbengued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long
LIBFT		=	printf/libftprintf.a
CC			=	cc -g3 #-fsanitize=address -g3
CFLAGS		=	-Wall -Wextra -Werror 
RM			= 	rm -f
SRCS		=	src/parsing/check_element.c \
				src/parsing/check_element_utils.c \
				src/parsing/check_map.c \
				src/parsing/is_it_playable.c \
				src/parsing/main_check.c \
				src/parsing/path_check.c \
				src/parsing/free_functons.c \
				src/rendering/animate_functions_enemy.c \
				src/rendering/animate_functions_other.c \
				src/rendering/animate_functions_player.c \
				src/rendering/movements_enemy_ran.c \
				src/rendering/check_functions.c \
				src/rendering/draw_functions_one.c \
				src/rendering/draw_functions_three.c \
				src/rendering/draw_functions_two.c \
				src/rendering/get_next_line.c \
				src/rendering/get_next_line_utils.c \
				src/rendering/init_var.c \
				src/rendering/init_xpm_addr.c \
				src/rendering/init_xpms.c \
				src/rendering/merge_functions.c \
				src/rendering/movements_enemy.c \
				src/rendering/movements_player.c \
				src/rendering/rendering.c \
				src/rendering/win_lose.c
OBJS		= 	$(SRCS:.c=.o)

all:		$(NAME)

$(LIBFT):
	make -C printf

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -lmlx -lXext -lX11 -o $(NAME)

clean:
	$(RM) -f $(OBJS)
	make clean -C printf

fclean: clean
	$(RM) $(NAME)
	make fclean -C printf

re: fclean all

.SECONDARY: $(OBJS)
