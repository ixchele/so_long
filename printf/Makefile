# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 11:46:45 by zbengued          #+#    #+#              #
#    Updated: 2025/01/04 21:00:10 by zbengued         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftprintf.a
NAME_B			= libftprintf_bonus.a
INCLUDE			= ../includes
LIBFT			= libft
SRC_DIR			= src/
SRC_BONUS_DIR	= src_bonus/
CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f
AR				= ar rcs
SRC_FILES		= ft_printf.c ft_printf_utils.c handlers_1.c handlers_2.c
SRC_FILES_BONUS = ft_printf_bonus.c ft_printf_utils_bonus.c handlers_1_bonus.c handlers_2_bonus.c
OBJ				= $(addprefix $(SRC_DIR), $(SRC_FILES:.c=.o))
OBJ_BONUS		= $(addprefix $(SRC_BONUS_DIR), $(SRC_FILES_BONUS:.c=.o))

all:		$(NAME)

bonus: all
	
$(NAME): $(OBJ_BONUS)
	make bonus -C $(LIBFT)
	make -C $(LIBFT)
	cp libft/libft.a .
	mv libft.a $(NAME)
	$(AR) $(NAME) $(OBJ_BONUS)

$(SRC_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	$(RM) -f $(OBJ) $(OBJ_BONUS)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)/libft.a
re: fclean all

.SECONDARY: $(OBJ_BONUS) $(OBJ)
