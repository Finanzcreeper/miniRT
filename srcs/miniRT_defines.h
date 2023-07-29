#ifndef MINIRT_DEFINES_H
# define MINIRT_DEFINES_H

# define STDIN		0
# define STDOUT		1
# define STDERR		2

# define M_PI		3.1415926535897
# define BG_R		20
# define BG_G		20
# define BG_B		20
# define BG_A		255
# define DEFAULT_A	255
# define COLOR_MAX	255
# define COLOR_MIN	0

# define SCENE_EXT	".rt"

# define ERR_ARG	"Wrong number of arguments!"
# define ERR_EXT	"Incorrect file format, scene file must be a .rt file!"
# define ERR_OPEN	"Failed to open scene file!"
# define ERR_EMPTY	"Scene file is empty!"
# define ERR_MALLOC	"Failed to malloc!"
# define ERR_TYPE	"Scene file contains undefined type!"
# define ERR_DUPA	"Scene file reassigning ambient lighting!"
# define ERR_DUPC	"Scene file reassigning camera!"
# define ERR_DUPL	"Scene file reassigning light!"
# define ERR_INFOA	"Scene file has incorrect ambient lighting info!"
# define ERR_INFOC	"Scene file has incorrect camera info!"
# define ERR_INFOL	"Scene file has incorrect light info!"
# define ERR_SP		"Scene file has incorret sphere!"
# define ERR_PL		"Scene file has incorret plane!"
# define ERR_CY		"Scene file has incorret cylinder!"
# define ERR_MISS	"Scene file doesn't have one of the required fields!"

#endif
