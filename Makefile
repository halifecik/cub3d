# Color Settings
BOLD    = \033[1m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
RESET   = \033[0m

# Compiler & Flags
CC      	= cc
INCLUDES 	= -Iincludes -Iminilibx-linux
CFLAGS  	= -Wall -Wextra -Werror $(INCLUDES)
MLXFLAGS	= -lmlx -lXext -lX11 -lm

# Directories
SRCDIR 	= src
OBJDIR  = obj
MLXDIR	= minilibx-linux
LIBFTDIR = includes/libft

# GNL (get_next_line) kaynak ve obje dosyaları
GNL_DIR = includes/gnl
GNL_SRC = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)

# Sources & Objects
SOURCES =	main.c \
            init/map.c \
            init/player.c \
            init/direction.c \
            init/initialize.c \
            init/raycast.c \
            init/graphics.c \
            init/config.c \
            parse/check_map.c \
            utils/parser_tools.c \
            raycast/raycast.c \
            raycast/calculate.c \
            raycast/render.c \
            raycast/texture.c \
            game/movement.c \
            game/rotation.c \
            game/game_loop.c \
            game/events.c \

SRCS	= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS    = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)) $(GNL_OBJ)
MLXLIB  = $(addprefix $(MLXDIR)/, libmlx.a)
LIBFT   = $(addprefix $(LIBFTDIR)/, libft.a)

# Output Binary
NAME    = cub3d

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
	@echo "$(MAGENTA)Build complete: libft$(RESET)"

$(MLXLIB):
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1
	@echo "$(MAGENTA)Build complete: minilibx$(RESET)"

$(NAME): $(LIBFT) $(MLXLIB) $(OBJS)
	@echo "$(CYAN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L $(MLXDIR) -L $(LIBFTDIR) $(MLXFLAGS) -lft -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@rm -f $(GNL_DIR)/*.o
	@$(MAKE) -C $(MLXDIR) clean
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo "$(RED)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re