NAME := cub3D
NAME_BONUS := cub3D_bonus
SRCDIR := src
OBJDIR := objs
OBJDIR_BONUS := objs_bonus
GNLDIR = get_next_line
CC := cc
CFLAGS := -Wall -Wextra -Werror

SRCS := src/bonus_textures.c src/cleanup.c src/cub3d.c src/doors.c src/enemy.c\
		src/environment.c src/events2.c src/events.c src/game_logic.c\
		src/get_next_line.c src/get_next_line_utils.c src/gun.c src/inits2.c\
		src/inits3.c src/inits.c src/load_textures.c src/minimap.c src/movement.c\
		src/raytrace_utils.c src/raytracing.c src/read_map.c src/read_map_content.c\
		src/read_map_utils.c src/render.c src/render_utils.c src/sprites.c\
		src/trig_utils.c src/unload_textures.c src/utils2.c src/utils3.c\
		src/utils4.c src/utils.c src/validate_map.c src/render_bonus.c

OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJS_BONUS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR_BONUS)/%.o)

ifeq ($(shell uname), Linux)
	INCLUDES = -I./includes -I./libft -I/usr/include -Imlx
else
	INCLUDES = -I./includes -I./libft -I/opt/X11/include -Imlx
endif

MLX_LIB = ./mlx/libmlx.a
LIBFT = ./libft/libft.a
BONUS_FLAGS = -D BONUS=true

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

$(OBJDIR_BONUS)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) $(BONUS_FLAGS) -c $< $(INCLUDES) -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(BONUS_FLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME_BONUS)

all: $(NAME)

bonus: $(NAME_BONUS)

$(MLX_LIB):
	@make -C ./mlx

$(LIBFT):
	@make -C ./libft

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@make clean -C ./libft
	@make clean -C ./mlx

fclean: clean
	@make fclean -C ./libft
	@make clean -C ./mlx
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: bonus all clean fclean re
