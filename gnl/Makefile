# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbumidan <pbumidan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 19:21:40 by pbumidan          #+#    #+#              #
#    Updated: 2024/10/15 17:50:40 by pbumidan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

SRCS = \
	get_next_line.c \
	get_all_lines.c \
	get_next_line_utils.c \

OBJS := $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)


$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)
	@echo "$(GREEN)gnl compiled!$(NC)"

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

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
