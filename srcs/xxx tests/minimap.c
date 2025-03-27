#include "cub3d.h"

//linear interpolation
//0 is equal to old_min
double	scale(double unscaled_num, double new_min,
	double new_max, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - 0) / (old_max - 0) + new_min);
}

//just for testing cases to set some colorvalues for wall, floor, player
t_color	*ft_coloring(int colorcode)
{
	t_color	*colorset;

	colorset = ft_calloc(1, sizeof(colorset));
	if (colorcode == 1)
	{
		colorset->red = 255;
		colorset->green = 255;
		colorset->blue = 255;
		colorset->alpha = 120;
	}
	else if (colorcode == 2)
	{
		colorset->red = 0;
		colorset->green = 0;
		colorset->blue = 0;
		colorset->alpha = 120;
	}
	else if (colorcode == 3)
	{
		colorset->red = 255;
		colorset->green = 0;
		colorset->blue = 0;
		colorset->alpha = 120;
	}
	return (colorset);
}

//to color each pixel of minimap
void	handle_pixel(t_gamedata *config, int x, int y, mlx_image_t *img)
{
	uint32_t	map_x;
	uint32_t	map_y;
	double		x_new;
	double		y_new;
	char		**map;

	map_x = ft_strlen(config->map[0]);
	map_y = ft_arrlen(config->map);
	x_new = scale(x, 0, map_x, img->width);
	y_new = scale(y, 0, map_y, img->height);
	map = config->map;
	printf("x: %f\n", x_new);
	printf("y: %f\n", y_new);
	if (map[(int)y_new][(int)x_new] == '0')
		putPixel(*ft_coloring(1), config->cub3d_data.img, x, y);
	else if (map[(int)y_new][(int)x_new] == '1'
		|| map[(int)y_new][(int)x_new] == ' ')
		putPixel(*ft_coloring(2), config->cub3d_data.img, x, y);
	else
		putPixel(*ft_coloring(3), config->cub3d_data.img, x, y);
}


void	ft_create_minimap(t_gamedata *config)
{
	mlx_image_t		*img;
	uint32_t		x;
	uint32_t		y;

	if (!(img = mlx_new_image(config->cub3d_data.mlx, 125, 95)))
	{
		mlx_close_window(config->cub3d_data.mlx);
		ft_error_handling(21, NULL, config);
	}
	x = 0;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			handle_pixel(config, x, y, img);
			x += 1;
		}
		y += 1;
	}

	if (mlx_image_to_window(config->cub3d_data.mlx, img, 0, 0) == -1)
	{
		mlx_close_window(config->cub3d_data.mlx);
		ft_error_handling(22, NULL, config);
	}
}
