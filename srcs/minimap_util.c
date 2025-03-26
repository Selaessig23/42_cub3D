/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:10:08 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/26 14:08:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief function to clear all pixels of the minimap image
 * by assigning the defined minimap background color to them 
 * (overwriting in case there had been a color before)
 */
void    clear_minimap_surface(t_gamedata *config, t_minimap_data minimap_data)
{
    int     i;
	int	    j;

    i = 0;
    j = 0;
    while (i < config->cub3d_data.minimap_surface->height)
    {
        j = 0;
        while (j < config->cub3d_data.minimap_surface->width)
        {
            putPixel(minimap_data.bg_color, config->cub3d_data.minimap_surface, j, i);
            j++;
        }
        i++;
    }
}
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
