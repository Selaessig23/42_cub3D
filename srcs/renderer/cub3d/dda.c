
#include "cub3d.h"

/**
 * DESCRIPTION:
 */

/**
 * @brief Digital Differential Analysis (DDA)
 * to find which squares of the map the ray hits, 
 * and stop the algorithm once a square that is a wall (or space) is hit
 * 
 * Steps:
 * 1) Jump to next map square, either in x-direction, or in y-direction
 *      (depending on which is closer)
 * 2) Check if ray has hit a wall (consider direction)
 *      hit_info->side = DIR_WEST --> Hit the west face (coming from east)
 *      hit_info->side = DIR_EAST --> Hit the east face (coming from west)
 *      hit_info->side = DIR_NORTH --> Hit the north face (coming from south)
 *      hit_info->side = DIR_SOUTH --> Hit the south face (coming from north)
 */
void	perform_dda(char **map, t_ray *ray, t_hit_info *hit_info)
{
	hit_info->hit = 0;

	while (!hit_info->hit) 
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			if (ray->step_x > 0)
				hit_info->side = DIR_WEST;
			else
				hit_info->side = DIR_EAST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			if (ray->step_y > 0)
				hit_info->side = DIR_NORTH;
			else
				hit_info->side = DIR_SOUTH;
		}
		if (map[ray->map_y][ray->map_x] == '1' 
			|| map[ray->map_y][ray->map_x] == ' ')
			hit_info->hit = 1;
	}
}
