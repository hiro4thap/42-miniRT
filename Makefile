# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 22:45:46 by jhughes           #+#    #+#              #
#    Updated: 2024/07/02 23:18:32 by jhughes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

COMPILER	= cc
CFLAGS		= -Wall -Wextra -Werror -MD $(INCL)
INCL		= -Iinc/ -Ilibft/inc/

ifeq ($(shell uname), Linux)
	INCL_LIB	= -L. -lft -lmlx_Linux  -lm
else
	INCL_LIB	= -L. -lft -lmlx -lm
endif

SRC_DIR		= src/
BONUS_DIR	= bonus/
O_DIR		= obj/

C_FILES		= main.c vector.c vector_operations.c vector_helpers.c utils.c \
				render.c
O_FILES		= $(C_FILES:.c=.o)
C_BONUS		= $(addprefix $(BONUS_DIR), $(C_FILES:.c=_bonus.c))
O_BONUS		= $(C_FILES:.c=_bonus.o) 

O_DEP 		= $(addprefix $(O_DIR), $(O_FILES))
O_BONUS_DEP	= $(addprefix $(O_DIR), $(O_BONUS))

LIB_DIR		= lib
LIBFT_DIR	= libft
LIBFT		= $(addsuffix .a, $(LIBFT_DIR))

ifeq ($(shell uname), Linux)
	LIBMLX_DIR 	= libmlx_Linux
	LIBMLX		= $(addsuffix .a, $(LIBMLX_DIR))
	MLX_FLAGS = -Lmlx -lmlx_Linux -L/usr/lib/X11 -lXext -lX11
else
	LIBMLX_DIR 	= libmlx
	LIBMLX		= $(addsuffix .dylib, $(LIBMLX_DIR))
	MLX_FLAGS = -framework OpenGL -framework AppKit
endif

all: $(NAME)

clean:
	$(MAKE) -C $(LIB_DIR)/$(LIBMLX_DIR) clean
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR) clean
	rm -rf $(O_DIR)

fclean: clean
	rm -f $(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT)
	rm -f $(LIB_DIR)/$(LIBMLX_DIR)/$(LIBMLX)
	rm -f $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

$(NAME): $(LIBMLX) $(LIBFT) $(O_DEP)
	$(COMPILER) $(CFLAGS) $(O_DEP) $(INCL_LIB) $(MLX_FLAGS) -o $(NAME)


libft: $(LIBFT)

mlx: $(LIBMLX)

ifeq ($(shell uname), Linux)
install-linux-dependencies:
	sudo dnf install libXpm-devel libX11-devel libXext-devel libbsd-devel
	sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev	
endif

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)/$(LIBFT_DIR)
	@cp $(LIB_DIR)/$(LIBFT_DIR)/$(LIBFT) .

$(LIBMLX):
	$(MAKE) -C $(LIB_DIR)/$(LIBMLX_DIR)
	@cp $(LIB_DIR)/$(LIBMLX_DIR)/$(LIBMLX) .

$(O_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@ $(INCLUDES)

$(O_DIR)%.o: $(SRC_DIR)$(BONUS_DIR)%.c
	@mkdir -p $(O_DIR)
	$(COMPILER) -c $(CFLAGS) $< -o $@ $(INCLUDES)

.PHONY: all clean fclean re bonus
