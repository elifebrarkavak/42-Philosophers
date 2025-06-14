SRCS = main.c \
		utils.c \
		init.c \
		process.c \
		program.c

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

OBJ := $(SRCS:.c=.o)

all: ${NAME}

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
