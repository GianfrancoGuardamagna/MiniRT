#include "minilibx-linux/mlx.h"
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>

#ifndef WIDTH
#define WIDTH 900
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_raytracer
{
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
}	t_raytracer;