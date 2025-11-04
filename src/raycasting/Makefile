# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 10:36:02 by zamohame          #+#    #+#              #
#    Updated: 2025/11/04 11:30:59 by zamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D

SRC         = render.c \
			  raycasting.c \
			  main.c

OBJ         = $(SRC:.c=.o)

MLX_DIR		= ../../minilibx-linux
MLX_FLAGS	= -L $(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
INCLUDES	= -I $(MLX_DIR) -I ./includes

CC          = gcc            
CFLAGS   	= -g -Wall -Wextra -Werror $(INCLUDES)

all: $(NAME)
$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(OBJ) $(MLX_FLAGS) -o $(NAME)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
