
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

/*
// Implements Bresenham's line algorithm to draw a line between two points.
void draw_line(mlx_image_t *surface, t_color color, t_vector2 start, t_vector2 end)
{
    int dx = fabs(end.x - start.x);
    int dy = fabs(end.y - start.y);
    int sx = 1;
    int sy = 1;
    int err = dx - dy;

    if (start.x >= end.x)
        sx = -1;
    if (start.y >= end.y)
        sy = -1;
    
    while (start.x != end.x || start.y != end.y)
    {
        putPixel(color, surface, start.x, start.y);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx) {
            err += dx;
            start.y += sy;
        }
    }
}

// Fills a triangle using scanline filling after sorting vertices by y-coordinate.
// This method ensures the triangle is processed from top to bottom, allowing
// horizontal scanlines to efficiently fill the shape.
void fill_triangle(mlx_image_t *surface, t_color color, t_vector2 v0, t_vector2 v1, t_vector2 v2)
{
    t_vector2 temp;
    int y, x;
    
    // Sort vertices by ascending y-coordinate to simplify scanline filling.
    if (v0.y > v1.y) { temp = v0; v0 = v1; v1 = temp; }
    if (v0.y > v2.y) { temp = v0; v0 = v2; v2 = temp; }
    if (v1.y > v2.y) { temp = v1; v1 = v2; v2 = temp; }
    
    y = v0.y;
    while (y <= v2.y)
    {
        // Compute scanline intersection points based on linear interpolation.
        int x_start = v0.x + (v2.x - v0.x) * (y - v0.y) / (v2.y - v0.y);
        int x_end = v0.x + (v1.x - v0.x) * (y - v0.y) / (v1.y - v0.y);
        if (y > v1.y)
            x_end = v1.x + (v2.x - v1.x) * (y - v1.y) / (v2.y - v1.y);
        
        // Fill pixels between computed x-values along the scanline.
        x = x_start;
        while (x <= x_end)
        {
            putPixel(color, surface, x, y);
            x++;
        }
        y++;
    }
}
*/

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

	t_vector2 left_vertex;
	t_vector2 right_vertex;
	t_vector2 perp_dir;

	color_view = (t_color){0xA9A9A880};
	player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
	dir_end = addvectors(player_pos, 
			multiplyvector(normalizevector(config->player.dir), 20));

	// Draw line from player position to direction end point
	// putPixel(color_view, config->cub3d_data.minimap_surface, player_pos.x, player_pos.x);
	putPixel(color_view, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);

	// Compute perpendicular direction for triangle's base.
	// perp_dir = (t_vector2){-config->player.dir.y, config->player.dir.x};
	// left_vertex = addvectors(player_pos, multiplyvector(perp_dir, 7));
	// right_vertex = addvectors(player_pos, multiplyvector(perp_dir, -7));

	// Draw the triangle edges.
	// draw_line(config->cub3d_data.minimap_surface, color_view, player_pos, left_vertex);
	// draw_line(config->cub3d_data.minimap_surface, color_view, player_pos, right_vertex);
	// draw_line(config->cub3d_data.minimap_surface, color_view, left_vertex, dir_end);
	// draw_line(config->cub3d_data.minimap_surface, color_view, right_vertex, dir_end);

	// Fill the triangle to make it solid.
	// fill_triangle(config->cub3d_data.minimap_surface, color_view, player_pos, left_vertex, right_vertex);

}
