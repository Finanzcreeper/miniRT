CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MAKEFLAGS = --no-print-directory
SRC = 
OBJ = $SRC(:.c=.o)
NAME = miniRT

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(NAME): $(OBJS)
	git submodule init

clean :
	@rm -f $(OBJ)  2>/dev/null

fclean : clean
	@rm -f $(NAME) 2>/dev/null
