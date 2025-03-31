
#include "cub3d.h"

/**
 * DESCRIPTION:
 */

/**
 * @brief 
 * 
 * 1) Calculate distance of perpendicular ray to avoid fisheye-effect
 * 2) Calculate where exactly the wall was hit
 */
static void	calculate_wall_properties(t_ray *ray, 
	t_hit_info *hit_info, t_vector2 player_pos)
{
	if (hit_info->side == DIR_EAST || hit_info->side == DIR_WEST)
		hit_info->perp_wall_dist = 
			(ray->map_x - player_pos.x + (1 - ray->step_x) / 2) / ray->dir.x;
	else
		hit_info->perp_wall_dist = 
			(ray->map_y - player_pos.y + (1 - ray->step_y) / 2) / ray->dir.y;
	if (hit_info->side == DIR_EAST || hit_info->side == DIR_WEST)
		ray->wall_x = player_pos.y + hit_info->perp_wall_dist * ray->dir.y;
	else
		ray->wall_x = player_pos.x + hit_info->perp_wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
}

/**
 * @brief
 * 
 * 1) Calculate height of line to draw on screen
 * 2) calculate lowest and highest pixel to fill in current stripe
 */
static void	calculate_render_line(t_render_line *line, mlx_image_t *img, 
	float perp_wall_dist, int screen_x)
{
	line->height = (int)(img->height / perp_wall_dist);
	line->screen_x = screen_x;
	line->draw_start = img->height / 2 - line->height / 2;
	if (line->draw_start < 0)
		line->draw_start = 0;
	line->draw_end = img->height / 2 + line->height / 2;
	if (line->draw_end >= img->height)
		line->draw_end = img->height - 1;
}

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
 * TODO: less parameter (max 4), avoid for-loop
 */
void copy_texture_line(mlx_image_t *render_img, mlx_image_t *texture,
	int screen_x, int draw_start, int draw_end, float wall_x)
{
	int		tex_x;
	int		tex_y;
	uint8_t	*pixel;
	float	step;

	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	for (int screen_y = draw_start; screen_y < draw_end; screen_y++)
	{
		step = (float)texture->height / (draw_end - draw_start);
		tex_y = (int)((screen_y - draw_start) * step);
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		putPixel(pixel_to_color(pixel), render_img, screen_x, screen_y);
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

/**
 * @brief Digital Differential Analysis (DDA)
 * to find which squares of the map the ray hits, 
 * and stop the algorithm once a square that is a wall (or space) is hit
 * 
 * Steps:
 * 1) Jump to next map square, either in x-direction, or in y-direction
 * 2) Check if ray has hit a wall
 */
static void	perform_dda(char **map, t_ray *ray, t_hit_info *hit_info)
{
	hit_info->hit = 0;

	while (!hit_info->hit) 
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			if (ray->step_x > 0)
				hit_info->side = DIR_WEST; // Hit the west face (coming from east)
			else
				hit_info->side = DIR_EAST; // Hit the east face (coming from west)
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			if (ray->step_y > 0)
				hit_info->side = DIR_NORTH; // Hit the north face (coming from south)
			else
				hit_info->side = DIR_SOUTH; // Hit the south face (coming from north)
		}
		if (map[ray->map_y][ray->map_x] == '1' 
			|| map[ray->map_y][ray->map_x] == ' ')
			hit_info->hit = 1;
	}
}


t_hit_info	init_hit_info(void)
{
	t_hit_info	hit_info;

	hit_info.hit = 0;
	hit_info.perp_wall_dist = 0;
	return (hit_info);
}

/**
 * @brief function that initiates the ray-struct
 * 	t_vector2 dir;        -> Ray direction: players pos considering camera and view adjustment
 *	t_vector2 delta_dist; -> Delta distance: Stores how far the ray has to travel along each axis 
 		(x and y) to move exactly one full tile in the respective direction.
		Taking the absolute value ensures that we always get a positive distance.
		If dir.x is large, delta_dist.x is small, meaning the ray advances quickly in the X direction.
		If dir.y is small, delta_dist.y is large, meaning the ray takes longer to move in the Y direction.
 *  t_vector2 side_dist;  // Side distance: distance from the 
 		current position to the next potential grid boundary
 *  int map_x;           // Current map x position
 *  int map_y;           // Current map y position
 *  int step_x;          // Step direction in x (-1 / 1)
 *  int step_y;          // Step direction in y (-1 / 1)
 *  float wall_x;        // Where exactly the wall was hit (esp. for texture mapping)
 * 
 * TODO: avoid terneries (? :), split function to 25 lines
 * 
 * 1e30 is scientific notation for 1×10301×1030, which is a very large floating-point number.
 * (used here as a substitute for infinity)
 * fabs (=returns the absolute value of a floating-point number)
 * fabs(1.0f / ray->dir.x) / fabs(1.0f / ray->dir.y) ensures that delta.dist is always positive
 * 
 * 
 */
static void init_ray(t_ray *ray, t_player player, float camera_x)
{
	ray->dir.x = player.dir.x + player.dir.y * camera_x * 0.66f; // Field of view adjustment
	ray->dir.y = player.dir.y - player.dir.x * camera_x * 0.66f; // Field of view adjustment
	ray->map_x = (int)player.pos.x;
	ray->map_y = (int)player.pos.y;
	ray->delta_dist.x = (ray->dir.x == 0) ? 1e30 : fabs(1.0f / ray->dir.x);
	ray->delta_dist.y = (ray->dir.y == 0) ? 1e30 : fabs(1.0f / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (player.pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0f - player.pos.x) 
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (player.pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0f - player.pos.y) 
			* ray->delta_dist.y;
	}
}


/**
 * @brief function that organises the raycasting of cub3d-img
 */
void	cast_ray_and_draw_wall(char **map, mlx_image_t *img, t_gamedata *config)
{
	t_ray			ray;
	t_hit_info		hit_info;
	t_render_line	line;
	int				x;
	float			camera_x;

	x = 0;
	while (x < img->width)
	{
		camera_x = 2.0f * x / (float)img->width - 1.0f;
		init_ray(&ray, config->player, camera_x);
		hit_info = init_hit_info();
		perform_dda(map, &ray, &hit_info);
		calculate_wall_properties(&ray, &hit_info, config->player.pos);
		calculate_render_line(&line, img, hit_info.perp_wall_dist, x);
		pick_and_place(hit_info.side, config, img, x, line.draw_start, 
			line.draw_end, ray.wall_x);
		x++;
	}
}

