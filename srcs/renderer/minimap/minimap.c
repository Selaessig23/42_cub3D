/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:10:08 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 18:03:07 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/cub3d.h"

/**
 * DESCRIPTION:
 * file that organises the rendering of minimap and handles the mode of 
 * the minimap (turned on / off)
 */

/**
 * @brief function to handle keyboard input to switch on / off the
 * minimap-display
 */
void	ft_minimap_switcher(t_gamedata *config)
{
	if (config->show_minimap)
	{
		config->show_minimap = false;
		mlx_set_instance_depth
			(&config->cub3d_data.img->instances[0], 1);
		mlx_set_instance_depth
			(&config->cub3d_data.minimap_surface->instances[0], 0);
	}
	else
	{
		config->show_minimap = true;
		mlx_set_instance_depth
			(&config->cub3d_data.img->instances[0], 0);
		mlx_set_instance_depth
			(&config->cub3d_data.minimap_surface->instances[0], 1);
	}
	printf("show minimap: %i\n", config->show_minimap);
}

/**
 * @brief function to clear all pixels of the minimap image
 * by assigning the defined minimap background color to them 
 * (overwriting in case there had been a color before)
 * each pixel of minimap will be rendered
 */
static void	clear_minimap_surface(t_gamedata *config,
	t_minimap_data minimap_data)
{
	unsigned int		i;
	unsigned int		j;

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
static void	fill_minimap_data(t_minimap_data *minimap_data, t_gamedata *config)
{
	minimap_data->cell_size = 32;
	minimap_data->map_y_len = ft_arrlen(config->map);
	minimap_data->map_x_len = ft_strlen(config->map[0]);
	if (minimap_data->map_x_len > minimap_data->map_y_len)
		minimap_data->minimap_size
			= minimap_data->map_x_len * minimap_data->cell_size;
	else
		minimap_data->minimap_size
			= minimap_data->map_y_len * minimap_data->cell_size;
	minimap_data->wall_color = (t_color){0xFFAAAAFF};
	minimap_data->floor_color = (t_color){0x66FF00AA};
	minimap_data->player_color = (t_color){0xFF0000FF};
	minimap_data->bg_color = (t_color){0x00333388};
}

/**
 * @brief main minimap function that orchestrates the drawing
 */
void	draw_minimap(t_gamedata *config)
{
	t_minimap_data	minimap_data;

	fill_minimap_data(&minimap_data, config);
	if (!config->show_minimap)
		return ;
	clear_minimap_surface(config, minimap_data);
	draw_minimap_grid(config, minimap_data);
	draw_player_position(config, minimap_data);
	draw_player_fov(config, minimap_data);
}
