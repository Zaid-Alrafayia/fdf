NAME = fdf
BONUS_NAME = fdf_bonus
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
BONUS_DIR = 
SRC = main.c init/validation.c init/init_matrix.c init/init_pixel.c utils/free.c window/pixel_gen.c init/scaling.c\
			window/window.c  window/rotate.c window/draw.c \
			window/line.c window/offset.c init/matrix.c
BONUS_SRC = main_bonus.c bonus/validation_bonus.c bonus/init_matrix_bonus.c bonus/init_pixel_bonus.c bonus/free_bonus.c bonus/pixel_gen_bonus.c bonus/scaling_bonus.c\
			bonus/window_bonus.c  bonus/rotate_bonus.c bonus/draw_bonus.c \
			bonus/line_bonus.c bonus/offset_bonus.c bonus/matrix_bonus.c bonus/movement_bonus.c



OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(NAME)
bonus :$(BONUS_NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_LIB) -lXext -lX11 -lm $(LDFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_LIB) $(LIBFT_LIB) -lXext -lX11 -lm  -o $(BONUS_NAME)
$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

%.o: %.c 
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME)_bonus $(MLX_LIB)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

