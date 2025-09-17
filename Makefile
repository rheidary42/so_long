# --- colors ---

RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
CYAN    := \033[0;36m
ORANGE  := \033[38;5;214m
RESET   := \033[0m
BOLD    := \033[1m

# --- config ---
NAME := so_long
HEADER := so_long.h
CFLAGS := -Wall -Wextra -Werror -g
LDFLAGS := -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd

LIBFT = libft/libft.a
FT_PRINTF = ft_printf/libftprintf.a

SRC = main.c\

OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	@cc $(SRC) $(LIBFT) $(FT_PRINTF) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉  executable $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"
	@echo ""
%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

# --- libraries ---

$(LIBFT):
	@make -sC libft
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)✅  libft.a $(YELLOW)   created ✅$(GREEN)   ║$(RESET)"	

$(FT_PRINTF):
	@make -sC ft_printf
	@echo "$(GREEN)║   $(ORANGE)✅  printf.a $(YELLOW)  created ✅$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"


# --- cleaning ---

c:
	@rm -f $(OBJS)
	@make clean -sC libft
	@make clean -sC ft_printf
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║   $(RED) 💀  objects removed  💀$(RED)    ║$(RESET)"
	@echo "$(RED)║  $(RED)💀 libft objects removed 💀$(RED)  ║$(RESET)"
	@echo "$(RED)║$(RED)💀 ft_printf objects removed 💀$(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""

f:
	@rm -f $(OBJS)
	@make clean -sC libft
	@make clean -sC ft_printf
	@rm -f $(NAME)
	@make fclean -sC libft
	@make fclean -sC ft_printf
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║   $(RED) 💀  objects removed  💀$(RED)    ║$(RESET)"
	@echo "$(RED)║  $(RED)💀 libft objects removed 💀$(RED)  ║$(RESET)"
	@echo "$(RED)║$(RED)💀 ft_printf objects removed 💀$(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║   $(RED)💀 executable removed  💀$(RED)   ║$(RESET)"
	@echo "$(RED)║   $(RED)💀   libft.a removed   💀$(RED)   ║$(RESET)"
	@echo "$(RED)║  $(RED) 💀 ft_printf.a removed 💀$(RED)   ║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""

re: f all
	@echo "$(CYAN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(CYAN)║   $(YELLOW)🔄   project rebuilt   🔄$(CYAN)   ║$(RESET)"
	@echo "$(CYAN)╚═══════════════════════════════╝$(RESET)"
	@echo ""

.PHONY: all c f re