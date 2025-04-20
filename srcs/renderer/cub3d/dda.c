/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:37:45 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/11 14:28:05 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EPSILON 0.0001

void	perform_dda(char **map, t_ray *ray, t_hit_info *hit_info)
{
	hit_info->hit = 0;
	hit_info->side = 0;
	
	while (!hit_info->hit)
	{
		if (fabs(ray->side_dist.x - ray->side_dist.y) < EPSILON)
		{
			// Corner case - check both directions
			bool hit_x = map[ray->map_y][ray->map_x + ray->step_x] == '1';
			bool hit_y = map[ray->map_y + ray->step_y][ray->map_x] == '1';
			if (hit_x && hit_y)
			{
				// Corner hit - choose closest
				if (ray->side_dist.x < ray->side_dist.y)
				{
					ray->side_dist.x += ray->delta_dist.x;
					ray->map_x += ray->step_x;
					hit_info->side = (ray->step_x > 0) ? DIR_WEST : DIR_EAST;
				}
				else
				{
					ray->side_dist.y += ray->delta_dist.y;
					ray->map_y += ray->step_y;
					hit_info->side = (ray->step_y > 0) ? DIR_NORTH : DIR_SOUTH;
				}
				hit_info->hit = 1;
				break;
			}
		}
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
