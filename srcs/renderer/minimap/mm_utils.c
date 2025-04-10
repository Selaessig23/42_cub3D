/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:33:09 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 19:47:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	putpixel(color_view, config->cub3d_data.minimap_surface,
		dir_end.x, dir_end.y);
}
