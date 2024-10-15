# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 19:21:40 by pbumidan          #+#    #+#              #
#    Updated: 2024/10/15 17:10:20 by pbumidan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

LIBFT = ../libft/libft.a

SRCS = \
	get_next_line.c \
	get_all_lines.c \

OBJS := $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I../libft

all: $(NAME)


$(NAME): $(OBJS) $(LIBFT)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)gnl compiled!$(NC)"

clean:
	@rm -f $(OBJS)
	@echo "$(YELLOW)The $(NAME) object files have been removed!$(NC)"

fclean:
	@rm -f $(NAME) $(OBJS)
	@echo "$(YELLOW)All the $(NAME)files have been removed!$(NC)"

re: fclean all

.PHONY: all clean fclean re

#colours
GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
NC = \033[0m
