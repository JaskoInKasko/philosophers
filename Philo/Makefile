CC = cc
CFLAGS = -Wall -Wextra -Werror -g
HEAD = philo.h
SRC = philo.c philo_utils.c threads.c actions.c\

OBJ = $(SRC:.c=.o)
NAME = philo

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -pthread $(OBJ) -o $(NAME)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
