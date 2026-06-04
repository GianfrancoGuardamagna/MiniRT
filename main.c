#include "mini_rt.h"
#include <stdio.h> //ELIMINAR

unsigned long createRGB(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

static void	pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

//render_sphere: Itera pixel por pixel de la ventana y calcula si está dentro del area del circulo, de ser así, lo pinta.
void render_sphere(t_raytracer *raytracer, t_sphere sphere)
{
	int x;
	int y;
	int dx;
	int dy;
	int radius;
	int radius_sq;

	radius = sphere.diameter / 2;
	radius_sq = pow(radius, 2);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			dx = x - sphere.x - (WIDTH / 2); // el - sphere.x es un desplazamiento de la posición
			dy = y + sphere.y - (HEIGHT / 2); // el + sphere.y es un desplazamiento de la posición (El eje Y está invertido)
			if (pow(dx, 2) + pow(dy, 2) <= radius_sq) //Pitagoras: x² + y² <= r² (r² es la hipotenusa, 'x' e 'y' son los catetos)
				pixel_put(&raytracer->img, x, y, sphere.color);
			x++;
		}
		y++;
	}
}

//render_light: Crea cada rayo individual de luz, ajustando el angulo y calculando los catetos va pintando pixel a pixel de cada rayo
void render_light(t_raytracer *raytracer, t_light light)
{
	int i;
	int end_of_screen;
	double step;
	double angle;
	double x_cathetus;
	double y_cathetus;

	i = 0;
	step = 1;
	while(i <= light.brightness) //Itera por cada rayo
	{
		angle = ((double) i / light.brightness) * (2 * PI); //Para cada rayo va a calcular el angulo en radianes xq (2PI es = 360 grados)
		end_of_screen = 0;
		x_cathetus = light.x; //Inicializa el punto desde el centro de la luz
		y_cathetus = light.y;
		while(!end_of_screen)
		{
			x_cathetus += cos(angle) * step; //Mide la variación en x para calcular la hipotenusa
			y_cathetus += sin(angle) * step;
			if(x_cathetus < 0 || x_cathetus > WIDTH || y_cathetus < 0 || y_cathetus > HEIGHT)
				end_of_screen = 1;
			else
				pixel_put(&raytracer->img, (int) x_cathetus, (int) y_cathetus, 0xffffffff);
		}
		i++;
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
			//if ((safe_area_y_neg >= y <= safe_area_y_pos) && (safe_area_x_neg >= x <= safe_area_x_pos))
				pixel_put(&raytracer->img, x, y, 0xffffffff);
			x++;
		}
		y++;
	}
}

int main(void)
{
	t_raytracer *raytracer;
	t_sphere sphere_1;
	t_sphere sphere_2;
	t_light light;

	/*------------------------------------------*/
	/*HARDCODEANDO LOS INPUTS*/
	sphere_1.diameter = 200;
	sphere_1.x = -200;
	sphere_1.y = -100;
	sphere_1.z = 0;
	sphere_1.color = createRGB(123, 456, 789);
	sphere_2.diameter = 300;
	sphere_2.x = 100;
	sphere_2.y = 100;
	sphere_2.z = 0;
	sphere_2.color = createRGB(789, 456, 123);
	light.x = 200;
	light.y = 100;
	light.z = 0;
	light.color = 0xffffffff;
	light.brightness = 100; //[0.0;1.0]
	/*------------------------------------------*/

	raytracer = malloc(sizeof(t_raytracer));
	if (!raytracer)
		return 1;
	raytracer->mlx_connection = mlx_init();
	raytracer->mlx_window = mlx_new_window(raytracer->mlx_connection, WIDTH, HEIGHT, "MiniRT");
	raytracer->img.img_ptr = mlx_new_image(raytracer->mlx_connection, WIDTH, HEIGHT);
	raytracer->img.pixels_ptr = mlx_get_data_addr(raytracer->img.img_ptr, &raytracer->img.bpp, &raytracer->img.line_len, &raytracer->img.endian);
	events_init(raytracer);

	render_sphere(raytracer, sphere_1);
	render_sphere(raytracer, sphere_2);
	render_light(raytracer, light);
	//create_square(raytracer, 500, 500);
	mlx_put_image_to_window(raytracer->mlx_connection, raytracer->mlx_window, raytracer->img.img_ptr, 0, 0);

	mlx_loop(raytracer->mlx_connection);
	raytracer_cleanup(raytracer);
	return 0;
}
