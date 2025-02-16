NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = srcs/main.c srcs/map_validation.c srcs/render.c srcs/player.c \
       srcs/get_next_line.c srcs/get_next_line_utils.c 
OBJS = $(SRCS:.c=.o)
MLX_DIR = ./minilibx_opengl
MLX = $(MLX_DIR)/libmlx.a
INCLUDES = -I includes -I $(MLX_DIR)
LIBS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all