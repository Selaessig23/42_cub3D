#include "cub3d.h"

static void	pixel_put(int x, int y, mlx_image_t *img, int color)
{
	int	offset;

	offset = (y * img->width) + (x * (img->pixels / 8));
	// *(unsigned int *)(img->addr + offset) = color;
	*(unsigned int *)((char *)img->addr + offset) = color;
}


static void	handle_pixel(int x, int y, t_gamedata *config)
{
	int	color;

	
	color = 
	pixel_put(x, y, &config->cub3d_data.img, color);
}

/**
 * @brief function to organise the rendering according to HEIGHT & WIDTH, 
 * touching all points on the x & y coordinates
 * 
 * @param config A pointer to the t_gamedata structure containing
 * the mlx / image / hook (?) data. 
 */
void	rendering(t_gamedata *config)
{
	int	x;
	int	y;

	y = 0;
	x = 1;
	while (y < config->window_height)
	{
		while (x < config->window_width)
		{
			handle_pixel(x, y, config);
			x += 1;
		}
		y += 1;
	}
	mlx_image_to_window(config->cub3d_data.mlx,
		config->cub3d_data.img,
		x, y);
}

