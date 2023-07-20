NAME = miniRT

CC = cc
RM = /bin/rm -rf

SRC = test.c
OBJ = $(SRC:.c=.o)

SRCDIR = src
LIBDIR = libft
MLXDIR = MLX42

LIBFT = $(LIBDIR)/libft.a
LIBMLX = $(MLXDIR)/build/libmlx42.a

MAKEFLAGS = --no-print-directory
CFLAGS = -Wall -Werror -Wextra -g3
IFLAGS	:= -I $(LIBDIR) -I $(MLXDIR)/include -I $(SRCDIR)

ifeq ($(shell uname -s), Darwin)
	LFLAGS = -L $(LIBDIR) -L $(MLXDIR)/build -lft -lmlx42 -lglfw \
				-L "/opt/homebrew/Cellar/glfw/3.3.8/lib"
else ifeq ($(shell uname -s), Linux)
	LFLAGS = -L $(LIBDIR) -L $(MLXDIR)/build -lft -lm -lmlx42 -ldl -lglfw \
				-pthread
endif

all : $(NAME)

$(NAME) : $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(IFLAGS)

$(LIBFT) :
	@git submodule init && git submodule update >/dev/null
	@echo "Building LIBFT..."
	@make -C $(LIBDIR) all >/dev/null

$(LIBMLX) :
	@git submodule init && git submodule update >/dev/null
	@echo "Building MLX42..."
	@cd $(MLXDIR); cmake -B build >/dev/null; cmake --build build -j4 >/dev/null

clean :
	$(RM) $(OBJ) 2>/dev/null
	@make $@ -C $(LIBDIR) >/dev/null

fclean : clean
	$(RM) $(NAME) $(LIBMLX) $(LIBFT) 2>/dev/null

re : fclean all

.PHONY : all clean fclean re
