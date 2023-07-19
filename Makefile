CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
MAKEFLAGS = --no-print-directory
SRC = test.c
OBJ = $(SRC:.c=.o)
NAME = miniRT

all : $(NAME)

$(NAME) : MLX libft update $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

libft : 
	make -C libft_with_additions

MLX : update
	cd MLX42; cmake -B build; cmake --build build -j4

update :
	git submodule init
	git submodule update

clean :
	@rm -f $(OBJ)  2>/dev/null
	@make clean -C libft_with_additions

fclean :
	@rm -f $(OBJ)  2>/dev/null
	@rm -f $(NAME) 2>/dev/null
	@make fclean -C libft_with_additions

re : fclean all

.PHONY : update clean fclean re
