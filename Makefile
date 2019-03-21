# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magrab   <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/16 17:28:51 by magrab            #+#    #+#              #
#    Updated: 2019/03/05 11:51:45 by magrab           ###   ########.fr        #
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
				./srcs/gpu_calcul.c \
				./srcs/draw_mandel.c \
				./srcs/draw_julia.c \
				./srcs/draw_ship.c \
				./srcs/draw_douady.c \
				./srcs/draw_galaxy.c \
				./srcs/draw_tricorn.c

OBJ				=	$(SRC:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror

FMLX		=	-lmlx -framework OpenGL -framework AppKit -framework OpenCL -o

all:		$(NAME)

$(NAME):	$(OBJ)
	make -C Libft
	gcc $(CFLAGS) $(FMLX) $(NAME) $(OBJ) $(LIB)

clean:
	make -C Libft clean
	rm -rf $(OBJ)

fclean:
	make -C Libft fclean
	rm -rf $(OBJ) $(NAME)

re:			fclean all

.PHONY : all clean fclean re clib fclib
