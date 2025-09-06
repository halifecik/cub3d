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

# Sources & Objects
SOURCES = 	main.c \
			utils/initiliaze.c \
			parser/flood_fill.c \
			parser/parse_cube.c \
			parser/parse_identifier.c \

SRCS	= $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS    = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
MLXLIB  = $(addprefix $(MLXDIR)/, libmlx.a)

# Output Binary
NAME    = cub3d

all: $(NAME)

$(MLXLIB):
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1
	@echo "$(MAGENTA)Build complete: minilibx$(RESET)"

$(NAME): $(MLXLIB) $(OBJS)
	@echo "$(CYAN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L $(MLXDIR) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete: $(NAME)$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	@echo "$(RED)Removing binary...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re