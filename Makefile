# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 09:42:46 by gda_cruz          #+#    #+#              #
#    Updated: 2023/02/13 11:31:35 by gda-cruz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN		=	\033[1;32m
LIGHT_GREEN	=	\033[0;32m
RED			=	\033[0;31m
YELLOW		=	\033[0;33m
RESET		=	\033[0m

NAME 		=	fdf
B_NAME 		=	checker

LIB_DIR		=	lib
LIBFT_DIR	=	$(LIB_DIR)/libft
MLX_DIR		=	$(LIB_DIR)/mlx_linux

SRC			=	srcs/main.c \
				srcs/adjustments.c srcs/line.c srcs/map_draw.c \
				srcs/pixel.c srcs/projection.c \
				srcs/height.c srcs/info.c srcs/keys.c \
				srcs/reset.c srcs/rotation.c srcs/translation.c \
				srcs/zoom.c \
				srcs/load_points.c srcs/map_setup.c srcs/read_file.c \
				srcs/colors_get.c srcs/colors_setup.c srcs/free.c \
				srcs/map_utils.c srcs/math.c

OBJ			=	$(SRC:srcs/%.c=$(OBJ_DIR)/%.o)
B_OBJ		=	$(B_SRC:srcs/bonus/%.c=$(B_OBJ_DIR)/%.o)
INC_DIR		=	inc
BUILD_DIR	=	./build
OBJ_DIR		=	$(BUILD_DIR)/objects
B_OBJ_DIR	=	$(BUILD_DIR)/b_objects

CC			=	gcc

CFLAGS		=	-g -Wall -Wextra -Werror
LIBFTFLAGS	=	-L$(LIBFT_DIR) -lft
MLXFLAGS	=	-L$(MLX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz
OFLAGS		=	-I/usr/include -I$(MLX_DIR) -O3

all: $(NAME)

$(NAME):	$(OBJ)
	@echo ""
	@echo "$(YELLOW)  Preparing FdF...$(RESET)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(LIGHT_GREEN)  Libft successfully compiled.$(RESET)"
	@make -s -C $(MLX_DIR)
	@echo "$(LIGHT_GREEN)  Minilibx successfully compiled.$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) $(LIBFTFLAGS) -o $(NAME)
	@echo "$(LIGHT_GREEN)  FdF successfully compiled.\n$(RESET)"

$(OBJ_DIR)/%.o:	srcs/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) $(OFLAGS) -c $(^) -o $(@)

.SILENT = $(OBJ)
.SILENT = $(B_OBJ)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR) $(B_OBJ_DIR)

bonus: $(B_OBJ)
	@echo ""
	@echo "$(YELLOW)  Preparing checker...$(RESET)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(LIGHT_GREEN)  Libft successfully compiled.$(RESET)"
	@$(CC) $(CFLAGS) -o $(B_NAME) $(^) -L$(LIBFT_DIR) -lft
	@echo "$(LIGHT_GREEN)  checker successfully compiled.\n$(RESET)"
	@mv $(B_NAME) build/bin

$(B_OBJ_DIR)/%.o:	srcs/bonus/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(^) -o $(@)

clean:
	@make clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(B_OBJ_DIR)

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf build fdf
	@echo "$(RED)  All FdF files removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus