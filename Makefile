
NAME = cub3D

LIBFT = ./libft/libft.a
GNL = ./gnl/gnl.a
MLX42 = ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

SRCS = \
	main.c \
	check_file.c \
	extract_comp.c \
	extract_color.c \
	extract_wall.c \
	map_extract.c \
	map_validate.c \
	map_create.c \
	map_fill.c \
	hook_game.c \
	hook_key.c \
	ray_cast.c \
	ray_render.c \
	utils.c \
	utils_free.c \

SRCS_SHARED = \

SRCS_BONUS = \

OBJS := $(SRCS:.c=.o)
OBJS_SHARED:= $(SRCS_SHARED:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I ./MLX42/include

all: $(NAME)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@ 

$(NAME): .mlx .libft .gnl $(OBJS) $(OBJS_SHARED)
	@cc $(CFLAGS) $(OBJS) $(OBJS_SHARED) $(LIBFT) $(GNL) $(MLX42) -o $(NAME)
	@echo "$(CYAN)* * * $(NAME) COMPLETE! * * *$(NC)"

.mlx:
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cmake ./MLX42 -B ./MLX42/build && make -s -C ./MLX42/build -j4
	@echo "$(MAGENTA)mlx42 cloned and built!$(NC)"
	@echo "$(GREEN)mlx42 compiled!$(NC)"
	@touch .mlx

.libft:
	@git clone https://github.com/pbumi/libft.git
	@make -s -C libft
	@touch .libft

.gnl:
	@git clone https://github.com/pbumi/gnl.git
	@make -s -C gnl
	@touch .gnl

bonus: .bonus
.bonus: .mlx .libft .gnl $(OBJS) $(OBJS_BONUS) $(OBJS_SHARED)
	@cc $(CFLAGS) $(OBJS_BONUS) $(OBJS_SHARED) $(LIBFT) $(GNL) $(MLX42) -o $(NAME_BONUS)
	@echo "$(CYAN)* * * $(NAME)_BONUS COMPLETE! * * *$(NC)"
	@touch .bonus

clean:
	@make -s clean -C libft
	@make -s clean -C gnl
	@rm -f $(OBJS) $(OBJ_BONUS) $(OBJS_SHARED)
	@echo "$(YELLOW)The $(NAME) object files have been removed!$(NC)"

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
