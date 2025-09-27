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

# GNL sources and objects
GNL_DIR = includes/gnl
GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c
GNL_OBJ = $(OBJDIR)/gnl/get_next_line.o $(OBJDIR)/gnl/get_next_line_utils.o

# Sources & Objects
SOURCES =	main.c \
            init/map.c \
            init/player.c \
            init/direction.c \
            init/raycast.c \
            init/graphics.c \
            init/config.c \
            parse/parse_map.c \
            parse/check_map.c \
            utils/utilities.c \
			utils/map_tools.c \
            raycast/raycast.c \
            raycast/calculate.c \
            raycast/render.c \
            raycast/texture.c \
            game/movement.c \
            game/rotation.c \
            game/loop.c \
            game/actions.c \
            game/doors.c \
			utils/cleanup/clean_config.c \
			utils/cleanup/clean_data.c \
			utils/cleanup/clean_graphics.c \
			utils/cleanup/clean_map.c \
			bonus/draw_minimap.c \
			bonus/draw_full_map.c \
			bonus/minimap_tools.c \

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

$(OBJDIR)/gnl/get_next_line.o: $(GNL_DIR)/get_next_line.c
	@mkdir -p $(OBJDIR)/gnl
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gnl/get_next_line_utils.o: $(GNL_DIR)/get_next_line_utils.c
	@mkdir -p $(OBJDIR)/gnl
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

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
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(LIBFTDIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re