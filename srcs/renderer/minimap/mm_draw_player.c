/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_draw_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:09:17 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 18:15:56 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#include "../include/cub3d.h"

static	void	drawline(t_color color, mlx_image_t *minimap_surface,
	t_vector2 start, t_vector2 end)
{
	t_vector2	delta;
	t_vector2	step;
	int			longest;
	int			i;

	delta = subtractvectors(end, start);
	if ((int)fabs(delta.x) > (int)fabs(delta.y))
		longest = (int)fabs(delta.x);
	else
		longest = (int)fabs(delta.y);
	step = dividevector(delta, longest);
	i = 0;
	while (i < longest)
	{
		if (start.x >= 0 && start.x < minimap_surface->width
			&& start.y >= 0 && start.y < minimap_surface->height)
		{
			putPixel(color, minimap_surface, (int)start.x, (int)start.y);
		}
		start = addvectors(start, step);
		i++;
	}
}

/**
 * DESCRIPTION:
 *
 */

/**
 * @brief the the position of the player
 * 1st new player pos is evaluated (considering cell size)
 * 2nd to draw a small filled (pixelated approximation of a)
 * circle around the player, a small 5 x 5 grid is defined
 * 3rd checks if the i,j are inside the circle
 * (using the circle formula: x2+y2≤r),
 * if yes: overwrite grid with players 5x5-grid
 */
void	draw_player_position(t_gamedata *config, t_minimap_data minimap_data)
{
	int			i;
	int			j;
	t_vector2	player_pos;

	player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
	i = -2;
	j = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (i * i + j * j <= 4)
				putPixel(minimap_data.player_color,
					config->cub3d_data.minimap_surface,
					player_pos.x + i, player_pos.y + j);
			j++;
		}
		i++;
	}
}

// Part 1: Initialize FOV data
void	init_fov_data(t_gamedata *config,
	t_minimap_data minimap_data, t_fov_data *fov_data)
{
	fov_data->fov_angle = 60 * (3.14 / 180.0);
	fov_data->radius = 20;
	fov_data->color_view = (t_color){0xA9A9A880};
	fov_data->surface = config->cub3d_data.minimap_surface;
	fov_data->player_pos = multiplyvector(config->player.pos,
			minimap_data.cell_size);
	fov_data->dir_angle = atan2(config->player.dir.y, config->player.dir.x);
	fov_data->left_angle = fov_data->dir_angle - (fov_data->fov_angle / 2);
	fov_data->right_angle = fov_data->dir_angle + (fov_data->fov_angle / 2);
	fov_data->dir_end = addvectors(fov_data->player_pos,
			multiplyvector(normalizevector(config->player.dir),
				fov_data->radius));
	fov_data->left_ray.x = fov_data->player_pos.x
		+ cos(fov_data->left_angle) * fov_data->radius;
	fov_data->left_ray.y = fov_data->player_pos.y
		+ sin(fov_data->left_angle) * fov_data->radius;
	fov_data->right_ray.x = fov_data->player_pos.x
		+ cos(fov_data->right_angle) * fov_data->radius;
	fov_data->right_ray.y = fov_data->player_pos.y
		+ sin(fov_data->right_angle) * fov_data->radius;
}

// Part 2: Draw FOV outline (direction line and side rays)
void	draw_fov_outline(t_fov_data *fov_data)
{
	drawline(fov_data->color_view,
		fov_data->surface, fov_data->player_pos, fov_data->dir_end);
	drawline(fov_data->color_view,
		fov_data->surface, fov_data->player_pos, fov_data->left_ray);
	drawline(fov_data->color_view,
		fov_data->surface, fov_data->player_pos, fov_data->right_ray);
}

// Part 3: Draw the FOV arc
void	draw_fov_arc(t_fov_data *fov_data)
{
	double		angle_step;
	double		current_angle;
	const int	segments = 20;
	int			i;
	t_vector2	next_point;

	if (fov_data->left_angle > fov_data->right_angle)
		fov_data->left_angle -= 2 * M_PI;
	angle_step = (fov_data->right_angle - fov_data->left_angle) / segments;
	current_angle = fov_data->left_angle;
	while (i < segments)
	{
		i++;
		current_angle += angle_step;
		next_point.x = fov_data->player_pos.x
			+ cos(current_angle) * fov_data->radius;
		next_point.y = fov_data->player_pos.y
			+ sin(current_angle) * fov_data->radius;
		drawline(fov_data->color_view,
			fov_data->surface, fov_data->left_ray, next_point);
		fov_data->left_ray = next_point;
	}
}

/**
 * @brief Draws the player's field of view on the minimap
 * 
 * This function renders the player's FOV as:
 * 1. A center direction line showing where the player is facing
 * 2. Two lines representing the left and right edges of the FOV
 * 3. An arc connecting the two edge lines to show the FOV area
 * 
 * @param config Game configuration containing player data
 * @param minimap_data Minimap data for scaling and positioning
 */
void	draw_player_fov(t_gamedata *config, t_minimap_data minimap_data)
{
	t_fov_data	fov_data;

	init_fov_data(config, minimap_data, &fov_data);
	draw_fov_outline(&fov_data);
	draw_fov_arc(&fov_data);
}

/**
 * @brief Draw the player direction line
 * 1st it sets a color for the direction view
 * 1st new player pos is evaluated (considering cell size)
 *
 */
void	draw_player_direction(t_gamedata *config, t_minimap_data minimap_data)
{
	t_vector2	player_pos;
	t_vector2	dir_end;
	t_color		color_view;


	color_view = (t_color){0xA9A9A880};
	player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
	dir_end = addvectors(player_pos,
			multiplyvector(normalizevector(config->player.dir), -10));

	putPixel(color_view, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);
}
