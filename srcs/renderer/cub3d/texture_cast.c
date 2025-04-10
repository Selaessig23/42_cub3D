
#include "cub3d.h"

/**
 * DESCRIPTION:
 */

/**
 * @brief function to set the color of the rendered texture-pixel
 */
t_color	pixel_to_color(uint8_t *pixel)
{
	t_color	color;

	color.red = pixel[0];
	color.green = pixel[1];
	color.blue = pixel[2];
	color.alpha = pixel[3];

	return (color);
}

/**
 * @brief 
 * 
 * TODO: less arguments (max 4), avoid for-loop
 */
void	copy_texture_line(mlx_image_t *render_img, mlx_image_t *texture,
	int screen_x, int draw_start, int draw_end, float wall_x)
{
	uint32_t		tex_x;
	uint32_t		tex_y;
	uint8_t	*pixel;
	float	step;
	int		screen_y;

	tex_x = (int)(wall_x * texture->width);
	// if (tex_x < 0)
	// 	tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	screen_y = draw_start;
	while (screen_y < draw_end)
	{
		step = (float)texture->height / (draw_end - draw_start);
		tex_y = (int)((screen_y - draw_start) * step);
		// if (tex_y < 0)
		// 	tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		putPixel(pixel_to_color(pixel), render_img, screen_x, screen_y);
		screen_y++;
	}
}

/**
 * @brief
 * 
 * TODO: less parameter (max 4)
 */
void pick_and_place(t_direction side, t_gamedata * config, mlx_image_t * img, 
	int x, int draw_start, int draw_end, float wall_x)
{
	mlx_image_t	*texture;

	if (side == DIR_NORTH)
		texture = config->cub3d_data.north;
	else if (side == DIR_SOUTH)
		texture = config->cub3d_data.south;
	else if (side == DIR_EAST)
		texture = config->cub3d_data.east;
	else
		texture = config->cub3d_data.west;
	copy_texture_line(img, texture, x, draw_start, draw_end, wall_x);
}
