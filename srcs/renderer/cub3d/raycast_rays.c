/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:13:56 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/22 17:11:19 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define EPSILON 0.0001

static	void	init_ray_direction(t_ray *ray, t_player player, double camera_x)
{
	ray->dir.x = player.dir.x + player.dir.y * camera_x * 0.66f;
	ray->dir.y = player.dir.y - player.dir.x * camera_x * 0.66f;
	check_and_epsilon(ray);
	ray->map_x = (int)player.pos.x;
	ray->map_y = (int)player.pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0f / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0f / ray->dir.y);
}

void	check_and_epsilon(t_ray *ray)
{
	if (fabs(ray->dir.x) < EPSILON)
	{
		if (ray->dir.x < 0)
			ray->dir.x = -EPSILON;
		else
			ray->dir.x = EPSILON;
	}
	if (fabs(ray->dir.y) < EPSILON)
	{
		if (ray->dir.y < 0)
			ray->dir.y = -EPSILON;
		else
			ray->dir.y = EPSILON;
	}
}

static	void	init_ray_step_distances(t_ray *ray, t_player player)
{
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

// Main function that calls both helper functions
void	init_ray(t_ray *ray, t_player player, double camera_x)
{
	init_ray_direction(ray, player, camera_x);
	init_ray_step_distances(ray, player);
}
