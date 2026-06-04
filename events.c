#include "mini_rt.h"

void	raytracer_cleanup(t_raytracer *raytracer)
{
	if (raytracer->img.img_ptr)
		mlx_destroy_image(raytracer->mlx_connection, raytracer->img.img_ptr);
	if (raytracer->mlx_window)
		mlx_destroy_window(raytracer->mlx_connection, raytracer->mlx_window);
	if (raytracer->mlx_connection)
	{
		mlx_destroy_display(raytracer->mlx_connection);
		free(raytracer->mlx_connection);
	}
	exit(1);
}

void	events_init(t_raytracer *raytracer)
{
	mlx_hook(raytracer->mlx_window, KeyPress, KeyPressMask, key_handler, raytracer);
	//mlx_hook(raytacer->mlx_window, ButtonPress, ButtonPressMask, mouse_handler, fractal);
	mlx_hook(raytracer->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, raytracer);
}

int	close_handler(t_raytracer *raytracer)
{
	mlx_destroy_image(raytracer->mlx_connection, raytracer->img.img_ptr);
	mlx_destroy_window(raytracer->mlx_connection, raytracer->mlx_window);
	mlx_destroy_display(raytracer->mlx_connection);
	free(raytracer->mlx_connection);
	exit(0);
}

int	key_handler(int keysym, t_raytracer *raytracer)
{
	if (keysym == XK_Escape)
		close_handler(raytracer);
	//else if (keysym == XK_Left)
	//	raytacer->shift_x += (0.5 * fractal->zoom);
	//fractal_render(fractal);
	return (0);
}