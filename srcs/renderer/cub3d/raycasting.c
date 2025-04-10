/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:40:06 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 22:22:52 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

/**
 * DESCRIPTION: this file organises the raycasting for cub3d-img
 * and initiates values for required structs
 * (t_hit_info, t_ray) as well
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
		hit_info->perp_wall_dist = (ray->map_x - player_pos.x
				+ (1 - ray->step_x) / 2) / ray->dir.x;
	else
		hit_info->perp_wall_dist = (ray->map_y - player_pos.y
				+ (1 - ray->step_y) / 2) / ray->dir.y;
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
	if ((unsigned int)line->draw_end >= img->height)
		line->draw_end = img->height - 1;
}

t_hit_info	init_hit_info(void)
{
	t_hit_info	hit_info;

	hit_info.hit = 0;
	hit_info.perp_wall_dist = 0;
	return (hit_info);
}

/**
 * @brief function that organises the raycasting of cub3d-img
 */
void	cast_ray_and_draw_wall(t_gamedata *config)
{
	t_ray			ray;
	t_hit_info		hit_info;
	t_render_line	line;
	uint32_t		x;
	float			camera_x;

	x = 0;
	while (x < config->cub3d_data.img->width)
	{
		camera_x = 2.0f * x / (float)config->cub3d_data.img->width - 1.0f;
		init_ray(&ray, config->player, camera_x);
		hit_info = init_hit_info();
		perform_dda(config->map, &ray, &hit_info);
		calculate_wall_properties(&ray, &hit_info, config->player.pos);
		calculate_render_line(&line,
			config->cub3d_data.img, hit_info.perp_wall_dist, x);
		copy_texture_line(config->cub3d_data.img,
			pick(hit_info.side, config), line, t_wall_slice{x, ray.wall_x});
		x++;
	}
}
