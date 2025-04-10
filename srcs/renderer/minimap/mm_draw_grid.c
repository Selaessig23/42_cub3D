/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_draw_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:36:08 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 22:38:30 by pvasilan         ###   ########.fr       */
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

static void fill_rect(mlx_image_t *surface, t_rect rect, t_color color)
{
    int dx;
    int dy;

    dy = 0;
    while (dy < rect.height)
    {
        dx = 0;
        while (dx < rect.width)
        {
            putpixel(color, surface, rect.x + dx, rect.y + dy);
            dx++;
        }
        dy++;
    }
}

static void draw_minimap_cell(t_gamedata *config, t_minimap_data minimap_data,
    int map_x, int map_y)
{
    t_color cell_color;
    t_rect  cell_rect;

    cell_rect.x = map_x * minimap_data.cell_size;
    cell_rect.y = map_y * minimap_data.cell_size;
    cell_rect.width = minimap_data.cell_size;
    cell_rect.height = minimap_data.cell_size;

    if (cell_rect.x >= minimap_data.minimap_size || cell_rect.y >= minimap_data.minimap_size)
        return;

    if (config->map[map_y][map_x] == '1' || config->map[map_y][map_x] == ' ')
        cell_color = minimap_data.wall_color;
    else
        cell_color = minimap_data.floor_color;

    if (cell_rect.x + cell_rect.width > minimap_data.minimap_size)
        cell_rect.width = minimap_data.minimap_size - cell_rect.x;

    if (cell_rect.y + cell_rect.height > minimap_data.minimap_size)
        cell_rect.height = minimap_data.minimap_size - cell_rect.y;

    fill_rect(config->cub3d_data.minimap_surface, cell_rect, cell_color);
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
