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
#ifndef PI
#define PI 3.14159265358979323846
#endif

//DEFINE COLORS

typedef struct s_sphere
{
	double	x;
	double	y;
	double	z;
	double	diameter;
	unsigned long color;

}	t_sphere;

typedef struct s_light
{
	double	x;
	double	y;
	double	z;
	double	brightness;
	unsigned long color;

}	t_light;

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

//Events
int		close_handler(t_raytracer *raytracer);
int		key_handler(int keysym, t_raytracer *raytracer);
void	events_init(t_raytracer *raytracer);
void	raytracer_cleanup(t_raytracer *raytracer);