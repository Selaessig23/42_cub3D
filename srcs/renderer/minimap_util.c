/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:10:08 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/27 16:34:14 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void draw_player_position(t_gamedata *config, t_minimap_data minimap_data)
{
    int i;
	int	j;
    t_vector2 player_pos;

    player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);

    i = -2;
    while (i <= 2)
    {
        j = -2;
        while (j <= 2)
        {
            if (i * i + j * j <= 4)
                putPixel(minimap_data.player_color, config->cub3d_data.minimap_surface,
                        player_pos.x + i, player_pos.y + j);
            j++;
        }
        i++;
    }
}

// 4. Draw the player direction line
void draw_player_direction(t_gamedata *config, t_minimap_data minimap_data)
{
    t_vector2 player_pos;
    t_vector2 dir_end;

    player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
    dir_end = addvectors(
        player_pos,
        multiplyvector(normalizevector(config->player.dir), 5)
    );

    // Draw line from player position to direction end point
    putPixel(minimap_data.player_color, config->cub3d_data.minimap_surface, player_pos.x, player_pos.y);
    putPixel(minimap_data.player_color, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);
}


/**
 * -----------------------------------------------------------------------------------------------------
 */



/**
 *  Draw a single cell of the minimap grid
 * 
 * TODO: decrease number of parameter to 4
 */ 
void	draw_minimap_cell(t_gamedata *config, t_minimap_data minimap_data,
	int map_x, int map_y, int screen_x, int screen_y)
{
	t_color	cell_color;
	int		cx;
	int		cy;

	if (screen_x >= minimap_data.minimap_size 
		|| screen_y >= minimap_data.minimap_size)
		return ;
	if (config->map[map_y][map_x] == '1' || config->map[map_y][map_x] == ' ')
		cell_color = minimap_data.wall_color;
	else
		cell_color = minimap_data.floor_color;
	cy = 0;
	while (cy < minimap_data.cell_size && screen_y 
		+ cy < minimap_data.minimap_size)
	{
		cx = 0;
		while (cx < minimap_data.cell_size && screen_x 
			+ cx < minimap_data.minimap_size)
		{
			putPixel(cell_color, config->cub3d_data.minimap_surface, 
				screen_x + cx, screen_y + cy);
			cx++;
		}
		cy++;
	}
}

/** 
 * @brief Draw the entire minimap grid 
 * (transform each tile into a pixel of minimap-image) 
 * by iterating through the map
 * 
 */
void	draw_minimap_grid(t_gamedata *config, t_minimap_data minimap_data)
{
	int	i;
	int	j;
	int	screen_x;
	int	screen_y;

	i = 0;
	while (i < minimap_data.map_y_len)
	{
		j = 0;
		while (j < minimap_data.map_x_len)
		{
			screen_x = j * minimap_data.cell_size;
			screen_y = i * minimap_data.cell_size;
			draw_minimap_cell(config, minimap_data, j, i, screen_x, screen_y);
			j++;
		}
		i++;
	}
}

/**
 * @brief function to clear all pixels of the minimap image
 * by assigning the defined minimap background color to them 
 * (overwriting in case there had been a color before)
 * each pixel of minimap will be rendered
 */
void	clear_minimap_surface(t_gamedata *config, t_minimap_data minimap_data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < config->cub3d_data.minimap_surface->height)
	{
		j = 0;
		while (j < config->cub3d_data.minimap_surface->width)
		{
			putPixel(minimap_data.bg_color, 
				config->cub3d_data.minimap_surface, j, i);
			j++;
		}
		i++;
	}
}

/**
 * @brief function to assign values to the minimap struct.
 * Each tile of the map-input is is drawn as a 
 * cell_size * cell_size pixel square.
 * The minimap size is calculated based on the larger dimension of the game map.
 * Otherwise a long map might be cut off.
 */
void	fill_minimap_data(t_minimap_data *minimap_data, t_gamedata *config)
{
	minimap_data->cell_size = 10;
	minimap_data->map_y_len = ft_arrlen(config->map);
	minimap_data->map_x_len = ft_strlen(config->map[0]);
	if (minimap_data->map_x_len > minimap_data->map_y_len)
		minimap_data->minimap_size = 
			minimap_data->map_x_len * minimap_data->cell_size;
	else
		minimap_data->minimap_size = 
			minimap_data->map_y_len * minimap_data->cell_size;
	minimap_data->wall_color = (t_color){0xFFAAAAFF};
	minimap_data->floor_color = (t_color){0x66FF00AA};
	minimap_data->player_color = (t_color){0xFF0000FF};
	minimap_data->bg_color = (t_color){0x33333388};
}

// 5. Main minimap function that orchestrates the drawing
void	draw_minimap(t_gamedata *config)
{
	t_minimap_data	minimap_data;

	fill_minimap_data(&minimap_data, config);
	if (!config->show_minimap)
		return;
	// Clear the minimap surface
	clear_minimap_surface(config, minimap_data);
	// Draw the map grid (walls and floor)
	draw_minimap_grid(config, minimap_data);
	// Draw the player position
	draw_player_position(config, minimap_data);
	// Draw the player direction
	draw_player_direction(config, minimap_data);
}
