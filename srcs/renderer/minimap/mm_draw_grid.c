/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:08 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 19:47:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

/**
 * DESCRIPTION:
 * int this file the grid of the minimap gets drawed
 */

/**
 * Draw a single cell of the minimap grid
 * screen_x && screen_y are simply
 * map_x * cell_size (== 10) && map_y * cell_size (== 10)
 * --> easy to simplify this function
 * maybe integrate linear interpolation
 */
static void	draw_minimap_cell(t_gamedata *config, t_minimap_data minimap_data,
	int map_x, int map_y)
{
	t_color	cell_color;
	int		cx;
	int		cy;

	cy = 0;
	cx = 0;
	if ((map_x * minimap_data.cell_size) >= minimap_data.minimap_size
		|| (map_y * minimap_data.cell_size) >= minimap_data.minimap_size)
		return ;
	if (config->map[map_y][map_x] == '1' || config->map[map_y][map_x] == ' ')
		cell_color = minimap_data.wall_color;
	else
		cell_color = minimap_data.floor_color;
	while ((cy < minimap_data.cell_size)
		&& (((map_y * minimap_data.cell_size) + cy)
			< minimap_data.minimap_size))
	{
		cx = 0;
		while (cx < minimap_data.cell_size
			&& ((map_x * minimap_data.cell_size) + cx)
			< minimap_data.minimap_size)
		{
			putpixel(cell_color, config->cub3d_data.minimap_surface,
				(map_x * minimap_data.cell_size) + cx,
				(map_y * minimap_data.cell_size) + cy);
			cx++;
		}
		cy++;
	}
}

/**
* @brief Draw the entire minimap grid (walls and floor)
* (transform each tile into a pixel of minimap-image)
* by iterating through the map
*
*/
void	draw_minimap_grid(t_gamedata *config, t_minimap_data minimap_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < minimap_data.map_y_len)
	{
		j = 0;
		while (j < minimap_data.map_x_len)
		{
			draw_minimap_cell(config, minimap_data, j, i);
			j++;
		}
		i++;
	}
}
