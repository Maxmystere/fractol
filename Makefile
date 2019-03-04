# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/16 17:28:51 by tferrieu          #+#    #+#              #
#    Updated: 2019/03/04 21:32:18 by magrab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

LIB			=	./Libft/libft.a

SRC-C		=	./srcs/camera_movement.c \
				./srcs/draw_line.c \
				./srcs/init_mlx.c \
				./srcs/input_hook.c \
				./srcs/loop_hook.c \
				./srcs/mlxmain.c \
				./srcs/program_close.c \
				./srcs/order_drawer.c \
				./srcs/draw_mandel.c \
				./srcs/draw_julia.c \
				./srcs/draw_ship.c

SRC-O		=	$(patsubst ./srcs/%.c, %.o, $(SRC-C))

FLAG		=	-Wall -Wextra -Werror

FMLX		=	-lmlx -framework OpenGL -framework AppKit -o

all:		$(NAME)

$(NAME):	$(SRC)
	make -C Libft
	gcc $(FLAG) -c $(SRC-C)
	gcc $(FLAG) $(FMLX) $(NAME) $(SRC-O) $(LIB)

clean:
	make -C Libft clean
	rm -rf $(SRC-O)

fclean:
	make -C Libft fclean
	rm -rf $(SRC-O) $(NAME)

re:			fclean all

.PHONY : all clean fclean re clib fclib
