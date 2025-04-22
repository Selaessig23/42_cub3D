/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:37:45 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/22 16:56:42 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EPSILON 0.0001

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
