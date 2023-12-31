# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 13:03:45 by mvomiero          #+#    #+#              #
#    Updated: 2023/07/17 18:30:41 by mvomiero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME	= miniRT

# Colors
RESET	= \e[0m
BOLD	= \e[1m
ITAL	= \e[3m
GREEN	= \e[32m

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -o3
LIBRARIES = $(MLX) $(LIBFT) -lm -lX11 -lXext

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Minilibx
MLX_PATH	= minilibx-linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# includes
INC_PATH	= ./includes/
INC			=	-I ./includes/ \
				-I ./libft/ \
				-I ./minilibx-linux/

# Sources
SRC_PATH	=	sources/
SRC			=	main.c \
				initialization/init.c \
				parse/parser.c \
				parse/parse_color.c \
				parse/parse_vector.c \
				parse/parse_ambient.c \
				parse/parse_camera.c \
				parse/parse_light.c \
				parse/parse_sphere.c \
				parse/parse_plane.c \
				parse/parse_cylinder.c \
				parse/parse_triangle.c \
				utils/error.c \
				utils/utils.c \
				utils/init_data.c \
				utils/init_mlx.c \
				utils/free_structs.c \
				utils/vectors.c \
				utils/vectors2.c \
				utils/vectors3.c \
				utils/color.c \
				render/render.c \
				render/render_viewport_matrix.c \
				render/render_get_ray.c \
				render/intersect_sphere.c \
				render/intersect_triangle.c \
				render/intersect_cylinder.c \
				render/intersect_cylinder_disks.c \
				render/intersect_cylinder_utils_t.c \
				render/intersect_plane.c \
				render/trace.c \
				render/shade.c \
				render/shade_soft.c \
				render/shade_hard.c \
				render/shade_is_in_shadow.c \
				render/shade_is_in_shadow_utils.c \
				controls/key_event.c \
				controls/transform_utils.c \
				controls/transform_camera.c \
				controls/transform_plane.c \
				controls/transform_triangle.c \
				controls/transform_utils_keycheck.c \
				controls/transform_cylinder.c \
				controls/transform_sphere.c \
				controls/transform_utils_vectors.c

SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all:$(MLX) $(LIBFT) $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@-$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARIES) $(INC)
	@echo "\n\t\$(BOLD)$(ITAL)$(GREEN) $(NAME) ready$(RESET)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_PATH)*.h
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH):
	@echo "Generating obj folders"
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)/initialization
	@mkdir $(OBJ_PATH)/parse
	@mkdir $(OBJ_PATH)/utils
	@mkdir $(OBJ_PATH)/render
	@mkdir $(OBJ_PATH)/controls

$(MLX):
	@echo "Making MiniLibX..."
	@make -sC $(MLX_PATH)

$(LIBFT):
	@echo "Making libft..."
	@make -sC $(LIBFT_PATH)
	@make clean -sC $(LIBFT_PATH)

clean:
	@echo "Removing .o object files..."
	@rm -rf $(OBJ_PATH)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

norminette:
	norminette ./sources
	norminette ./libft
	norminette -R CheckForbiddenSourceHeader ./includes

test:
	@python3 test.py

valgrind:
	valgrind  --track-origins=yes --track-fds=yes --leak-check=full --show-leak-kinds=all -s ./miniRT scenes/simple_scenes/sphere.rt


.PHONY: all re clean fclean norminette valgrind