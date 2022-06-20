NAME = cub3d

LIBFT = libft/
LIB =

SRCS =	srcs/main.c	\
		srcs/utils/get_next_line.c \
		srcs/utils/get_next_line_utils.c \
		srcs/parsing/check_content.c \
		srcs/parsing/empty_space.c \
		srcs/parsing/check_map.c \
		srcs/parsing/check_border.c \
		srcs/utils/free_utils.c \
		srcs/parsing/check_space.c \
		srcs/parsing/check_limit.c \
		srcs/parsing/error.c \
		srcs/parsing/check_rgb.c

OBJ		= ${SRCS:.c=.o}
OBJS	= *.o
CC		= gcc
CFLAGS	= -Wall -Wextra #-Werror

all :
	@make bonus -C $(LIBFT)
	@make $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I include/

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) -I libft/ -I include/ $(OBJ) libft/libft.a -o $(NAME) $(LIB)

key :#a retirer
	cd ./mlx_linux && make && cd ..
	$(CC) srcs/key_handling.c -L./mlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o key

clean :
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ:.o=.d)

fclean : clean
		@rm -rf libft.a
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(NAME)

re :	fclean
		@make all
.PHONY			:	all clean fclean re
