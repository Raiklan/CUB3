SRCS = main.c bresenham.c prep_wd.c render.c utils.c get_next_line.c libft.c ft_split.c
C.O = ${SRCS:.c=.o}
H = fdf.h
NAME = fdf
CC = gcc
FLAGS = -Wall -Wextra -Werror
LEAK = -fsanitize=address

all : $(NAME)

$(NAME) :
# 	cd ./mlx_linux && make && cd ..
	$(CC) $(FLAGS) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm  -o $(NAME) #remove -lz after -lm

leak :
	$(CC) $(FLAGS) $(LEAK) -D BUFFER_SIZE=1 $(SRCS) -L./mlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o fdfleak

clean :
	rm -f $(C.O)

fclean : clean
	rm -f $(NAME)

re : fclean all
