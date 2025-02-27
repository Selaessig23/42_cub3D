/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:58:44 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/27 17:03:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
//Drawing functions

//this should take the color format and the window size and create a surface filled with black
//this surface will be used for rendering
mlx_texture_t* createSurface(t_gamedata *config){
	mlx_texture_t *surface;

	surface = malloc(sizeof(mlx_texture_t));
	surface->width = config->window_width;
	surface->height = config->window_height;
	surface->pixels = malloc(sizeof(t_color) * config->window_width * config->window_height);
	for (int i = 0; i < config->window_width * config->window_height; i++){
		surface->pixels[i] = 0x000000;
	}

	return (surface);
}

//this function draws a pixel of parameter color at position x,y on the surface
void putPixel(t_color color, mlx_texture_t *surface, int x, int y) {
	int pixel_index;

	pixel_index = 0;
    if (x >= 0 && x < surface->width && y >= 0 && y < surface->height) {
        pixel_index = (y * surface->width + x) * 4;
        surface->pixels[pixel_index] = color.red;
        surface->pixels[pixel_index + 1] = color.green;
        surface->pixels[pixel_index + 2] = color.blue;
        surface->pixels[pixel_index + 3] = color.alpha;
    }
}

//for minimap - here we should use the MINIMAP drawing surface
void drawLine(t_color color, mlx_texture_t *minimap_surface, t_vector2 start, t_vector2 end)
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
		putPixel(color, minimap_surface, (int)start.x, (int)start.y);
		start = addvectors(start, step);
		i++;
	}
}

//this function fills the top half of the surface with the ceiling color
void fillCeiling(t_gamedata *config){
	const t_color color = *config->ceiling;

	for (int y = 0; y < config->window_height / 2; y++){
		for (int x = 0; x < config->window_width; x++){
			putPixel(color, config->cub3d_data.current_surface, x, y);
		}
	}
}

//this function fills the bottom half of the surface with the floor color
void fillFloor(t_gamedata *config){
	const t_color color = *config->floor;

	for (int y = config->window_height / 2; y < config->window_height; y++){
		for (int x = 0; x < config->window_width; x++){
			putPixel(color, config->cub3d_data.current_surface, x, y);
		}
	}
}
