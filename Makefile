NAME = miniRT

_DIR = parser utils calc
_SRC = main.c init.c mlx_hooks.c render.c color.c transformation.c \
       parser/basic.c parser/object.c parser/params.c parser/utils.c \
	   parser/parser.c \
	   calc/vector.c calc/vec_rotate.c calc/basic.c calc/intersection.c \
	   calc/shadow.c calc/inside.c calc/facing_ratio.c calc/cylinder.c \
       utils/ft_read_file.c utils/ft_strarr.c utils/ft_exit.c
_INC = miniRT_defines.h miniRT_types.h miniRT.h
SRC = $(addprefix $(SRCDIR)/, $(_SRC))
INC = $(addprefix $(SRCDIR)/, $(_INC))
OBJ = $(addprefix $(OBJDIR)/, $(_SRC:.c=.o))

CC = cc
RM = /bin/rm -rf

OBJDIR = objs
SRCDIR = srcs
LIBDIR = libft
MLXDIR = MLX42

LIBFT = $(LIBDIR)/libft.a
LIBMLX = $(MLXDIR)/build/libmlx42.a

MUTE = >/dev/null
MAKEFLAGS = --no-print-directory
CFLAGS = -Wall -Werror -Wextra -g3
DEBUGFLAGS = -g3
IFLAGS = -I $(LIBDIR) -I $(MLXDIR)/include -I $(SRCDIR)

ifeq ($(shell uname -s), Darwin)
	LFLAGS = -L $(LIBDIR) -L $(MLXDIR)/build -lft -lmlx42 -lglfw \
				-L "/opt/homebrew/Cellar/glfw/3.3.8/lib"
else ifeq ($(shell uname -s), Linux)
	LFLAGS = -L $(LIBDIR) -L $(MLXDIR)/build -lft -lm -lmlx42 -ldl -lglfw \
				-pthread
endif

all : $(NAME)

$(NAME) : $(LIBFT) $(LIBMLX) $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LFLAGS)

$(LIBFT) :
	@git submodule init $(MUTE) && git submodule update --remote $(MUTE)
	@echo "Building LIBFT..."
	@make -C $(LIBDIR) $(MUTE)

$(LIBMLX) :
	@git submodule init $(MUTE) && git submodule update --remote $(MUTE)
	@echo "Building MLX42..."
	@cd $(MLXDIR); cmake -B build $(MUTE); cmake --build build -j4 $(MUTE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@mkdir -p $(OBJDIR) && cd $(OBJDIR) && mkdir -p $(_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(IFLAGS)

clean :
	$(RM) $(OBJ)
	@test -f $(LIBDIR)/Makefile && make $@ -C $(LIBDIR) $(MUTE)

fclean : clean
	$(RM) $(NAME) $(LIBMLX) $(LIBFT)
	@git submodule deinit --all -f $(MUTE)

re : fclean all

.PHONY : all clean fclean re
