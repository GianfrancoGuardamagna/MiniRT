#include "mini_rt.h"
#include <stdio.h> //ELIMINAR

static void	pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void create_circle(t_raytracer *raytracer, int diameter)
{
	int x;
	int y;
	int dx;
	int dy;
	int radius;
	int radius_sq;

	radius = diameter / 2;
	radius_sq = radius * radius;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dx = x - (WIDTH / 2);
			dy = y - (HEIGHT / 2);
			if ((dx * dx) + (dy * dy) <= radius_sq)
				pixel_put(&raytracer->img, x, y, 0xffffffff);
			x++;
		}
		y++;
	}
}

void create_square(t_raytracer *raytracer, int height, int width)
{
	int x;
	int y;
	int safe_area_x_pos;
	int safe_area_x_neg;
	int safe_area_y_pos;
	int safe_area_y_neg;

	safe_area_x_neg = (WIDTH / 2) - (height / 2);
	safe_area_x_pos = WIDTH - (height / 2);
	safe_area_y_neg = (HEIGHT / 2) - (width / 2);
	safe_area_y_pos = HEIGHT - (width / 2);

	printf("%d %d %d %d", safe_area_x_neg, safe_area_x_pos, safe_area_y_neg, safe_area_y_pos);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if ((safe_area_y_neg >= y <= safe_area_y_pos) && (safe_area_x_neg >= x <= safe_area_x_pos))
				pixel_put(&raytracer->img, x, y, 0xffffffff);
			x++;
		}
		y++;
	}
}

int main(void)
{
	t_raytracer *raytracer;

	raytracer = malloc(sizeof(t_raytracer));
	if (!raytracer)
		return 1;
	raytracer->mlx_connection = mlx_init();
	raytracer->mlx_window = mlx_new_window(raytracer->mlx_connection, WIDTH, HEIGHT, "MiniRT");
	raytracer->img.img_ptr = mlx_new_image(raytracer->mlx_connection, WIDTH, HEIGHT);
	raytracer->img.pixels_ptr = mlx_get_data_addr(raytracer->img.img_ptr, &raytracer->img.bpp, &raytracer->img.line_len, &raytracer->img.endian);

	//create_circle(raytracer, 500);
	create_square(raytracer, 500, 500);
	mlx_put_image_to_window(raytracer->mlx_connection, raytracer->mlx_window, raytracer->img.img_ptr, 0, 0);

	//mlx_loop(raytracer->mlx_connection);
	return 0;
}
