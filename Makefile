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
CFLAGS := -g -I. -I./libs/minilibx-linux
# -Wall -Wextra -Werror
LDFLAGS := -L./libs/minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

LIBFT = libs/libft/libft.a
FT_PRINTF = libs/ft_printf/libftprintf.a

SRC = 	main.c \
		src/map_validation/map_validation.c \
		src/map_validation/flood_fill.c \
		src/xpm_handling/xpm_init.c \
		src/helpers/helper1.c\
		src/game_logic/hooks.c\

OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF) $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)🎉  executable $(YELLOW)created 🎉$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"
	@echo ""
%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

# --- libraries ---

$(LIBFT):
	@make -sC libs/libft
	@echo "$(GREEN)╔═══════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║   $(ORANGE)✅  libft.a $(YELLOW)   created ✅$(GREEN)   ║$(RESET)"	

$(FT_PRINTF):
	@make -sC libs/ft_printf
	@echo "$(GREEN)║   $(ORANGE)✅  printf.a $(YELLOW)  created ✅$(GREEN)   ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════╝$(RESET)"


# --- cleaning ---

c:
	@rm -f $(OBJS)
	@make clean -sC libs/libft
	@make clean -sC libs/ft_printf
	@echo "$(RED)╔═══════════════════════════════╗$(RESET)"
	@echo "$(RED)║   $(RED) 💀  objects removed  💀$(RED)    ║$(RESET)"
	@echo "$(RED)║  $(RED)💀 libft objects removed 💀$(RED)  ║$(RESET)"
	@echo "$(RED)║$(RED)💀 ft_printf objects removed 💀$(RED)║$(RESET)"
	@echo "$(RED)╚═══════════════════════════════╝$(RESET)"
	@echo ""

f:
	@rm -f $(OBJS)
	@make clean -sC libs/libft
	@make clean -sC libs/ft_printf
	@rm -f $(NAME)
	@make fclean -sC libs/libft
	@make fclean -sC libs/ft_printf
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