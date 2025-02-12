# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 16:17:43 by zbengued          #+#    #+#              #
#    Updated: 2025/02/11 17:00:31 by zbengued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= so_long
B_NAME			= so_long_bonus
INCLUDE			= include
LIBFT			= ft_printf/libftprintf.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror 
RM				= rm -f
SRC				= rendering.c draw_functions_tow.c get_next_line_utils.c merge_functions.c animate_functions_player.c check.c draw_functions.c \
				  movments.c animate_functions_enemy.c check_functions.c draw_functions_t.c get_next_line.c
#SRC_FILES_BONUS = ft_printf_bonus.c ft_printf_utils_bonus.c handlers_1_bonus.c handlers_2_bonus.c
OBJ				= $(SRC:.c=.o)
#OBJ_BONUS		= $(addprefix $(SRC_BONUS_DIR), $(SRC_FILES_BONUS:.c=.o))

all:		$(NAME)

$(LIBFT):
	make -C ft_printf
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lm -lmlx -lXext -lX11 -o $(NAME)

clean:
	$(RM) -f $(OBJ) $(OBJ_BONUS)
	make clean -C ft_printf

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all

.SECONDARY: $(OBJ)

