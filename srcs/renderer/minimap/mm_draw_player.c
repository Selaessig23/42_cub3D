
#include "../include/cub3d.h"

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
				putPixel(minimap_data.player_color, config->cub3d_data.minimap_surface,
						player_pos.x + i, player_pos.y + j);
			j++;
		}
		i++;
	}
}

/**
 * @brief Draw the player direction line
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
			multiplyvector(normalizevector(config->player.dir), 20));

	// Draw line from player position to direction end point
	// putPixel(color_view, config->cub3d_data.minimap_surface, player_pos.x, player_pos.x);
	putPixel(color_view, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);
// 	double		x = player_pos.x;
// 	double		y = player_pos.y;
// 	while (y < dir_end.y)
// 	{
// 		x = player_pos.x;
// 		while (x < dir_end.x)
// 		{
// 			putPixel(color_view, config->cub3d_data.minimap_surface, x, y);
// 			x++;
// 		}
// 		y += 1;
// 	}
}
