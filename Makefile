# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 16:17:43 by zbengued          #+#    #+#              #
#    Updated: 2025/02/23 16:37:44 by zbengued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long
NAME_BNS	=	so_long_bonus
LIBFT		=	printf/libftprintf.a
CC			=	cc -fsanitize=address -g3
CFLAGS		=	#-Wall -Wextra -Werror 
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
				src/rendering/rendering.c
SRCS_BNS	=	src_bns/parsing/check_element.c \
				src_bns/parsing/check_element_utils.c \
				src_bns/parsing/check_map.c \
				src_bns/parsing/is_it_playable.c \
				src_bns/parsing/main_check.c \
				src_bns/parsing/path_check.c \
				src_bns/parsing/free_functons.c \
				src_bns/rendering/animate_functions_enemy.c \
				src_bns/rendering/animate_functions_other.c \
				src_bns/rendering/animate_functions_player.c \
				src_bns/rendering/movements_enemy_ran.c \
				src_bns/rendering/check_functions.c \
				src_bns/rendering/draw_functions_one.c \
				src_bns/rendering/draw_functions_three.c \
				src_bns/rendering/draw_functions_two.c \
				src_bns/rendering/get_next_line.c \
				src_bns/rendering/get_next_line_utils.c \
				src_bns/rendering/init_var.c \
				src_bns/rendering/init_xpm_addr.c \
				src_bns/rendering/init_xpms.c \
				src_bns/rendering/merge_functions.c \
				src_bns/rendering/movements_enemy.c \
				src_bns/rendering/movements_player.c \
				src_bns/rendering/rendering.c \
				src_bns/rendering/win_lose.c
OBJS		= 	$(SRCS:.c=.o)
OBJS_BNS	= 	$(SRCS_BNS:.c=.o)

all:		$(NAME)

bonus:		$(NAME_BNS)

$(LIBFT):
	make -C printf

$(NAME_BNS): $(OBJS_BNS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BNS) $(LIBFT) -lm -lmlx -lXext -lX11 -o $(NAME_BNS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -lmlx -lXext -lX11 -o $(NAME)

clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(OBJS_BNS)
	make clean -C printf

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BNS)
	make fclean -C printf

re: fclean all

.SECONDARY: $(OBJS) $(OBJS_BNS)

