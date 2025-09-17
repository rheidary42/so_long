RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
CYAN    := \033[0;36m
RESET   := \033[0m
BOLD    := \033[1m
ORANGE  := \033[38;5;214m

NAME := libft.a
BONUS_NAME := .bonus
HEADER := libft.h
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS = BUILT-IN NAMING CONVETION, AUTOMATICALLY USED;
SRC := ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_strlen.c\
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_strlcpy.c\
	ft_strlcat.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strncmp.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strnstr.c\
	ft_atoi.c\
	ft_calloc.c\
	ft_strdup.c\
	ft_substr.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_split.c\
	ft_itoa.c\
	ft_strmapi.c\
	ft_striteri.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\

BONUS := ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c\

OBJS := $(SRC:.c=.o)
BONUS_OBJS := $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS) $(BONUS_OBJS)
	@ar r $(NAME) $(OBJS) $(BONUS_OBJS)
	@touch .bonus
	@echo "libft.a created with bonus"

clean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(BONUS_NAME)

fclean:
	@rm -f $(OBJS) $(BONUS_OBJS) $(BONUS_NAME)
	@rm -f $(NAME)

re: fclean bonus

.PHONY: all clean fclean re