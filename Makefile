# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/16 17:28:51 by tferrieu          #+#    #+#              #
#    Updated: 2019/03/05 11:42:52 by magrab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

LIB			=	./Libft/libft.a

SRC			=	./srcs/camera_movement.c \
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

#OBJ			=	$(patsubst ./srcs/%.c, ./objs/%.o, $(SRC))
OBJ				=	$(SRC:.c=.o)

FLAG		=	-Wall -Wextra -Werror

FMLX		=	-lmlx -framework OpenGL -framework AppKit -o

all:		$(NAME)

$(NAME):	$(OBJ)
	make -C Libft
	gcc $(FLAG) $(FMLX) $(NAME) $(OBJ) $(LIB)



clean:
	make -C Libft clean
	rm -rf $(OBJ)

fclean:
	make -C Libft fclean
	rm -rf $(OBJ) $(NAME)

re:			fclean all

.PHONY : all clean fclean re clib fclib
