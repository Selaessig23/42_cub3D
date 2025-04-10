
#include "../include/cub3d.h"

static void drawLine(t_color color, mlx_image_t *minimap_surface, t_vector2 start, t_vector2 end)
{
    t_vector2 delta;
    t_vector2 step;
    int longest;
    int i;

    delta = subtractvectors(end, start);
    longest = (int)fabs(delta.x) > (int)fabs(delta.y) ? (int)fabs(delta.x) : (int)fabs(delta.y);
    step = dividevector(delta, longest);
    i = 0;
    while (i < longest)
    {
        if (start.x >= 0 && start.x < minimap_surface->width && 
            start.y >= 0 && start.y < minimap_surface->height)
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
				putPixel(minimap_data.player_color, config->cub3d_data.minimap_surface,
						player_pos.x + i, player_pos.y + j);
			j++;
		}
		i++;
	}
}

void draw_player_fov(t_gamedata *config, t_minimap_data minimap_data)
{
    t_vector2 player_pos;
    t_vector2 dir_end;
    t_vector2 left_ray, right_ray;
    t_color color_view;
    double fov_angle = 60 * (3.14 / 180.0); // Convert FOV angle to radians
    
    color_view = (t_color){0xA9A9A880};
    player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
    
    // Calculate the main direction ray
    dir_end = addvectors(player_pos, 
            multiplyvector(normalizevector(config->player.dir), 20));
    
    // Draw the center direction line
    drawLine(color_view, config->cub3d_data.minimap_surface, player_pos, dir_end);
    
    // Calculate left and right edges of FOV
    double dir_angle = atan2(config->player.dir.y, config->player.dir.x);
    double left_angle = dir_angle - (fov_angle / 2);
    double right_angle = dir_angle + (fov_angle / 2);
    
    // Calculate the endpoints for left and right FOV rays
    left_ray.x = player_pos.x + cos(left_angle) * 20;
    left_ray.y = player_pos.y + sin(left_angle) * 20;
    
    right_ray.x = player_pos.x + cos(right_angle) * 20;
    right_ray.y = player_pos.y + sin(right_angle) * 20;
    
    // Draw the FOV edges
    drawLine(color_view, config->cub3d_data.minimap_surface, player_pos, left_ray);
    drawLine(color_view, config->cub3d_data.minimap_surface, player_pos, right_ray);
    // Optional: Draw an arc connecting the edges to visualize FOV area
    // This would require an additional arc drawing function
}

/*
// Draws a line between two points using MiniLibX's pixel drawing function.
void draw_line(mlx_image_t *img, t_color color, t_vector2 start, t_vector2 end)
{
    int dx = fabs(end.x - start.x);
    int dy = fabs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (start.x != end.x || start.y != end.y)
    {
        putPixel(color, img, start.x, start.y);
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            start.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            start.y += sy;
        }
    }
}

// Draws a filled triangle using MiniLibX's pixel function.
void fill_triangle(mlx_image_t *img, t_color color, t_vector2 v0, t_vector2 v1, t_vector2 v2)
{
    t_vector2 temp;
    int y, x;
    
    // Sort vertices by ascending y-coordinate.
    if (v0.y > v1.y) { temp = v0; v0 = v1; v1 = temp; }
    if (v0.y > v2.y) { temp = v0; v0 = v2; v2 = temp; }
    if (v1.y > v2.y) { temp = v1; v1 = v2; v2 = temp; }
    
    y = v0.y;
    while (y <= v2.y)
    {
        int x_start = v0.x + (v2.x - v0.x) * (y - v0.y) / (v2.y - v0.y);
        int x_end = v0.x + (v1.x - v0.x) * (y - v0.y) / (v1.y - v0.y);
        if (y > v1.y)
            x_end = v1.x + (v2.x - v1.x) * (y - v1.y) / (v2.y - v1.y);
        
        x = x_start;
        while (x <= x_end)
        {
            putPixel(color, img, x, y);
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


	color_view = (t_color){0xA9A9A880};
	player_pos = multiplyvector(config->player.pos, minimap_data.cell_size);
	dir_end = addvectors(player_pos, 
			multiplyvector(normalizevector(config->player.dir), 10));

	putPixel(color_view, config->cub3d_data.minimap_surface, dir_end.x, dir_end.y);


}
