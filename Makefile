CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MAKEFLAGS = --no-print-directory
SRC = test.c
OBJ = $(SRC:.c=.o)
NAME = miniRT

all : $(NAME)

$(NAME) : update $(OBJ)
	git submodule init
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

update :
	git submodule update

clean :
	@rm -f $(OBJ)  2>/dev/null

fclean : clean
	@rm -f $(NAME) 2>/dev/null

re : fclean all

.PHONY : update clean fclean re
