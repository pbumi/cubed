# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 19:29:39 by pbumidan          #+#    #+#              #
#    Updated: 2024/10/07 15:45:07 by pbumidan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cubed
# NAME_BONUS = so_long_bonus

LIBFT = ./libft/libft.a
GNL = ./gnl/gnl.a
MLX42 = ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
#-L"/Users/$(USER)/.brew/opt/glfw/lib/"
# -I include -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS = \
	main.c \

SRCS_SHARED = \

SRCS_BONUS = \


OBJS := $(SRCS:.c=.o)
OBJS_SHARED:= $(SRCS_SHARED:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -I ./MLX42/include

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

$(NAME): .mlx .libft .gnl $(OBJS) $(OBJS_SHARED)
	@cc $(CFLAGS) $(OBJS) $(OBJS_SHARED) $(LIBFT) $(GNL) $(MLX42) -o $(NAME)
	@echo "$(CYAN)* * * $(NAME) COMPLETE! * * *$(NC)"

.mlx:
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4
	@echo "$(MAGENTA)mlx42 cloned and built!$(NC)"
	@echo "$(GREEN)mlx42 compiled!$(NC)"
	@touch .mlx

.libft:
	@git clone https://github.com/pbumi/libft.git
	@make -C libft
	@touch .libft

.gnl:
	@git clone https://github.com/pbumi/gnl.git
	@make -C gnl
	@touch .gnl

bonus: .bonus
.bonus: .mlx .libft .gnl $(OBJS) $(OBJS_BONUS) $(OBJS_SHARED)
	@cc $(CFLAGS) $(OBJS_BONUS) $(OBJS_SHARED) $(LIBFT) $(GNL) $(MLX42) -o $(NAME_BONUS)
	@echo "$(CYAN)* * * SO_LONG_BONUS COMPLETE! * * *$(NC)"
	@touch .bonus

clean:
	@rm -f $(OBJS) $(OBJ_BONUS) $(OBJS_SHARED)
	@rm -rf ./MLX42
	@echo "$(YELLOW)The mlx42 objects have been removed!$(NC)"
	@echo "$(YELLOW)The so_long object files have been removed!$(NC)"

fclean:
	@rm -rf ./libft
	@echo "$(YELLOW)All the libft files have been removed!$(NC)"
	@rm -rf ./gnl
	@echo "$(YELLOW)All the gnl files have been removed!$(NC)"
	@rm -rf ./MLX42
	@echo "$(YELLOW)All the mlx42 files have been removed!$(NC)"
	@rm -f $(NAME) $(NAME_BONUS) $(OBJS_SHARED) $(OBJS) $(OBJS_BONUS) .bonus .libft .gnl .mlx

re: fclean all

.PHONY: all clean fclean re bonus mlx

#colours
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
MAGENTA = \033[0;95m
NC = \033[0m

# NAME = cubed

# SRCS = \
# 		main.c \

# OBJS := $(SRCS:.c=.o)

# CFLAGS = -Wall -Wextra -Werror

# all: $(NAME)

# %.o: %.c
# 	@cc $(CFLAGS) -c $<

# $(NAME): $(OBJS)
# 	@cc $(CFLAGS) -o $(NAME) $(OBJS)
# 	@echo "$(CYAN)* * * PHILO COMPLETE! * * *$(NC)"

# clean:
# 	@rm -f $(OBJS)
# 	@echo "$(YELLOW)* The object files have been removed! *$(NC)"

# fclean: clean
# 	@rm -f $(NAME)
# 	@echo "$(MAGENTA)* * * CLEANED EVERYTHING! * * *$(NC)"

# re: fclean all

# .PHONY: all clean fclean re bonus

# #Color ANSI Code
# RED    := \033[91;1m
# GREEN  := \033[92;1m
# YELLOW := \033[93;1m
# BLUE   := \033[94;1m
# MAGENTA   := \033[95;1m
# CYAN      := \033[96;1m
# WHITE     := \033[97;1m
# RESET     := \x1b[0m #reseting the text formatting to default state

