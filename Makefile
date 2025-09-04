# ==================== #
#    Color Settings    #
# ==================== #
BOLD    = \033[1m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

# Compiler & Flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes
MLXFLAGS	= -lmlx -lXext -lX11 -lm

# Directories
SRCDIR 	= src
OBJDIR  = obj
MLXDIR	= minilibx-linux

MLXLIB		= $(MLX_DIR)/libmlx.a

# Sources & Objects
SOURCES = main.c \

SRCS	= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS    = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
MLXLIB  = $(addprefix $(MLX_DIR)/, libmlx.a)

# Output Binary
NAME    = cub3d

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@echo "$(CYAN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L $(MLX_DIR) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re