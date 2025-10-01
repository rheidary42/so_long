RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
CYAN    := \033[0;36m
RESET   := \033[0m
BOLD    := \033[1m
ORANGE  := \033[38;5;214m

NAME := libftprintf.a
HEADER := libftprintf.h
CC := @cc
CFLAGS := -Wall -Wextra -Werror -g
SRC := ft_printf.c\
	utils.c\
	mem_to_str.c\

OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(NAME)
	@rm -f $(OBJS)

re: fclean all

.PHONY: all clean fclean re