CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MAKEFLAGS = --no-print-directory
SRC = test.c
OBJ = $(SRC:.c=.o)
NAME = miniRT

all : $(NAME)

$(NAME): $(OBJ)
	git submodule init
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean :
	@rm -f $(OBJ)  2>/dev/null

fclean : clean
	@rm -f $(NAME) 2>/dev/null
