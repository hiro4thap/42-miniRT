

#include "../inc/miniRT.h"

#include <math.h>
#include <stdio.h>

t_bool	sphere_intersection(t_sphere sphere, t_vector line)
{
	t_vector o;
	set_vector_components(&o, 0, 0, 0);
	double grad;


	grad = pow(dot(line, subtract(o, sphere.position)), 2.0);
	grad -= pow(magnitude(subtract(o, sphere.position)), 2.0) - pow((sphere.diameter / 2.0), 2.0);
	print_vector(sphere.position);
	print_vector(line);
	printf("%lf\n", grad);
	if (grad >= 0)
		return (TRUE);
	return (FALSE);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	set_color(t_color col)
{
	int	color;

	color = col.b
		+ (col.g << 8)
		+ (col.r << 16);
	return (color);
}

void	generate_image(t_data *image, t_program *program)
{
	(void) program;
	int		width = 640;
	int		height = 480;
	double	rad_conversion = M_PI / 180.0;
	
	t_sphere sphere;

	set_vector_components(&sphere.position, 0.0, 0.0, 4.0);
	sphere.color.b = 0;
	sphere.color.g = 250;
	sphere.color.r = 250;
	sphere.diameter = 2.0;

	t_camera	camera;
	camera.fov = 90.0;
	set_vector_components(&camera.orientation, 0.0, 1.0, 0.0);
	set_vector_components(&camera.direction, 0.0, 0.0, 1.0);
	set_vector_components(&camera.position, 0.0, 0.0, 0.0);
	t_vector	b, bn, vn;
	b = cross(camera.direction, camera.orientation);
	bn = normalise(b);
	vn = normalise(camera.orientation);

	double	gx, gy;
	gx = tan(camera.fov * rad_conversion);
	gy = gx * ((double)(height - 1)) / ((double) (width - 1));

	t_vector	qx, qy;
	qx = scalar_product(bn, (2.0 * gx)/((double) (width - 1)));
	qy = scalar_product(vn, (2.0 * gy)/((double) (height - 1)));

	t_vector	last_pixel;
	last_pixel = subtract(subtract(camera.direction, scalar_product(bn,gx)), scalar_product(camera.orientation, gy));

	t_vector	pixel, ray;
	int i, j;
	j = 1;
	while (j <= height)
	{
		i = 1;
		while (i <= width)
		{
			pixel = add(add(last_pixel, scalar_product(qx, (i - 1))), scalar_product(qy, (j - 1)));
			ray = normalise(pixel);
			if (sphere_intersection(sphere, ray))
			{
				set_pixel(image, i, j, set_color(sphere.color));
				print_vector(ray);
			}
			i += 1;
		}
		j += 1;
	}
}

int render_frame(t_program *program)
{
	t_data	image;

	image.img = mlx_new_image(program->mlx_pointer, 640, 480);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, 
				&image.line_length, &image.endian);
	generate_image(&image, program);
	mlx_put_image_to_window(program->mlx_pointer, program->window, image.img, 0, 0);
	mlx_destroy_image(program->mlx_pointer, image.img);
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	t_program	program;

	(void) argc;
	(void) argv;
	program.mlx_pointer = mlx_init();
	program.window = mlx_new_window(program.mlx_pointer, 640, 480, "miniRT");
	render_frame(&program);
	mlx_loop(program.mlx_pointer);
	mlx_destroy_window(program.mlx_pointer, program.window);
	free(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
