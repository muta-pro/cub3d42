NAME = cub3D
NAME_B = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -ffast-math -O3

SRCDIR = src
OBJDIR = obj
OBJDIR_B = obj_b
INCDIR = includes
MLXDIR = MLX42
LIBFTDIR = ./libft

SRC_BOTH = grid.c \
		init_game.c \
		main.c \
		hooks.c \
		map_load.c \
		map_header.c \
		player_movement_utils.c \
		player_movement.c \
		raycasting.c \
		render.c \
		rgb.c \
		tex_utils.c \
		textures.c \
		split_pars.c \
		start_player.c \
		validation.c \
		cleanup.c \
		utils_pars.c
SRC_BNS = bns/init_b.c \
		bns/bonus_mouse.c \
		bns/bonus_minimap.c \
		bns/bonus_doors.c \
		bns/bonus_sprites.c \
		bns/draw_mini.c \
		bns/draw_spr.c
SRC_SHARED = player_rotation.c mand_bots.c
#obj path generation
OBJS = $(addprefix $(OBJDIR)/, $(SRC_BOTH:.c=.o) $(SRC_SHARED:.c=.o))
OBJS_B = $(addprefix $(OBJDIR_B)/, $(SRC_BOTH:.c=.o) $(SRC_BNS:.c=.o))

INCLUDE = -I$(INCDIR) -I$(MLXDIR)/include -I$(LIBFTDIR) -I./
LIBFT = $(LIBFTDIR)/libft.a
MLX_LIB = $(MLXDIR)/build/libmlx42.a -lglfw -ldl -pthread -lm
MLX_A = $(MLXDIR)/build/libmlx42.a

all: $(NAME)

bonus : $(NAME_B)

$(NAME): $(OBJS) $(LIBFT) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

$(NAME_B): $(OBJS_B) $(LIBFT) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS_B) $(LIBFT) $(MLX_LIB) -o $(NAME_B)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR_B)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFTDIR) --no-print-directory

$(MLX_A):
	@cmake -S $(MLXDIR) -B $(MLXDIR)/build
	@make -C $(MLXDIR)/build -j4

clean:
	@rm -rf $(OBJDIR) $(OBJDIR_B)
	@make -C $(LIBFTDIR) clean --no-print-directory
fclean: clean
	@rm -rf $(NAME) $(NAME_B)
	@make -C $(LIBFTDIR)  fclean --no-print-directory
re: fclean all

.PHONY: all clean fclean re bonus
