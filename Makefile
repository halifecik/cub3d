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
OBJDIR_BONUS = obj_bonus
MLXDIR	= minilibx-linux
LIBFTDIR = includes/libft

# GNL sources and objects
GNL_DIR = includes/gnl
GNL_SRC = $(GNL_DIR)/get_next_line.c \
          $(GNL_DIR)/get_next_line_utils.c
GNL_OBJ = $(OBJDIR)/gnl/get_next_line.o $(OBJDIR)/gnl/get_next_line_utils.o
GNL_OBJ_BONUS = $(OBJDIR_BONUS)/gnl/get_next_line.o $(OBJDIR_BONUS)/gnl/get_next_line_utils.o

# Mandatory Sources
MANDATORY_SOURCES =	main.c \
					init/map.c \
					init/player.c \
					init/direction.c \
					init/raycast.c \
					init/graphics.c \
					init/config.c \
					parse/parse_map.c \
					parse/check_map.c \
					raycast/raycast.c \
					raycast/calculate.c \
					raycast/render.c \
					raycast/texture.c \
					game/movement.c \
					game/rotation.c \
					game/loop.c \
					game/actions.c \
					utils/cleanup/clean_config.c \
					utils/cleanup/clean_data.c \
					utils/cleanup/clean_graphics.c \
					utils/cleanup/clean_map.c \
					utils/render.c \
					utils/map.c \
					utils/utilities.c

# Bonus Sources (includes all mandatory + bonus features)
BONUS_SOURCES = $(MANDATORY_SOURCES) \
				game/mouse_bonus.c \
				bonus/minimap/draw_minimap_bonus.c \
				bonus/minimap/draw_full_map_bonus.c \
				bonus/minimap/minimap_tools_bonus.c \
				bonus/door/door_action_bonus.c \
				bonus/door/door_manager_bonus.c \
				bonus/door/door_utils_bonus.c \
				bonus/sprite/initialize_bonus.c \
				bonus/sprite/update_bonus.c \
				bonus/sprite/sort_bonus.c \
				bonus/sprite/render_bonus.c \
				bonus/sprite/interface_bonus.c \
				bonus/sprite/texture_bonus.c \
				bonus/sprite/calculate_bonus.c

MANDATORY_SRCS = $(addprefix $(SRCDIR)/, $(MANDATORY_SOURCES))
BONUS_SRCS = $(addprefix $(SRCDIR)/, $(BONUS_SOURCES))

MANDATORY_OBJS = $(addprefix $(OBJDIR)/, $(MANDATORY_SOURCES:.c=.o)) $(GNL_OBJ)
BONUS_OBJS = $(addprefix $(OBJDIR_BONUS)/, $(BONUS_SOURCES:.c=.o)) $(GNL_OBJ_BONUS)

MLXLIB  = $(addprefix $(MLXDIR)/, libmlx.a)
LIBFT   = $(addprefix $(LIBFTDIR)/, libft.a)

# Output Binaries
NAME = cub3d
BONUS_NAME = cub3d_bonus

all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)
	@echo "$(MAGENTA)Build complete: libft$(RESET)"

$(MLXLIB):
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1
	@echo "$(MAGENTA)Build complete: minilibx$(RESET)"

# Mandatory GNL objects
$(OBJDIR)/gnl/get_next_line.o: $(GNL_DIR)/get_next_line.c
	@mkdir -p $(OBJDIR)/gnl
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/gnl/get_next_line_utils.o: $(GNL_DIR)/get_next_line_utils.c
	@mkdir -p $(OBJDIR)/gnl
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus GNL objects
$(OBJDIR_BONUS)/gnl/get_next_line.o: $(GNL_DIR)/get_next_line.c
	@mkdir -p $(OBJDIR_BONUS)/gnl
	@echo "$(YELLOW)Compiling $< (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS=1 -c $< -o $@

$(OBJDIR_BONUS)/gnl/get_next_line_utils.o: $(GNL_DIR)/get_next_line_utils.c
	@mkdir -p $(OBJDIR_BONUS)/gnl
	@echo "$(YELLOW)Compiling $< (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS=1 -c $< -o $@

# Mandatory binary
$(NAME): $(LIBFT) $(MLXLIB) $(MANDATORY_OBJS)
	@echo "$(CYAN)Linking mandatory objects...$(RESET)"
	@$(CC) $(CFLAGS) $(MANDATORY_OBJS) -L $(MLXDIR) -L $(LIBFTDIR) $(MLXFLAGS) -lft -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

# Bonus binary
$(BONUS_NAME): $(LIBFT) $(MLXLIB) $(BONUS_OBJS)
	@echo "$(CYAN)Linking bonus objects...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS=1 $(BONUS_OBJS) -L $(MLXDIR) -L $(LIBFTDIR) $(MLXFLAGS) -lft -o $(BONUS_NAME)
	@echo "$(GREEN)Build complete: $(BONUS_NAME)$(RESET)"

# Mandatory object compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Bonus object compilation
$(OBJDIR_BONUS)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $< (bonus)...$(RESET)"
	@$(CC) $(CFLAGS) -DBONUS=1 -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(LIBFTDIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)Removing binaries...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re