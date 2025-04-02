/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:58:44 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/02 15:36:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//Drawing functions

mlx_image_t	*createSurface(t_gamedata *config)
{
	mlx_image_t		*img;
	uint32_t		x;
	uint32_t		y;

	y = 0;
	x = 0;
	img = config->cub3d_data.img;
	// memset(img->pixels, 240, img->width * (img->height / 2) * sizeof(int32_t));
	// memset(&(img->pixels[img->width * (img->height / 2) * sizeof(int32_t)]), 160, img->width * (img->height / 2) * sizeof(int32_t));
	// printf ("img-height: %i, img_width: %i\n", img->height, img->width);
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if (y < img->height / 2)
				putPixel(*config->ceiling, config->cub3d_data.img, x, y);
			else
				putPixel(*config->floor, config->cub3d_data.img, x, y);
			x += 1;
		}
		y += 1;
	}
	ft_create_minimap(config);
	return (img);
}
/*
//this should take the color format and the window size and create a surface filled with black
//this surface will be used for rendering
mlx_texture_t* createSurface(t_gamedata *config)
{
	mlx_texture_t	*surface;
	// uint32_t		x;
	// uint32_t		y;

	// y = 0;
	// x = 1;
	surface = malloc(sizeof(mlx_texture_t));
	if (!surface)
		ft_error_handling(9, NULL, config);
	surface->width = config->window_width;
	surface->height = config->window_height;
	surface->pixels = malloc(sizeof(t_color) * config->window_width * config->window_height);
	for (int i = 0; i < config->window_width * config->window_height; i++){
		surface->pixels[i] = 0x000000;
	}
	// config->cub3d_data.current_surface = surface;
	// fillCeiling(config);
	// fillFloor(config);
	config->cub3d_data.current_surface =
		mlx_load_png("/home/mstracke/development/cub3D/test/purple_stone.png");
	if (!config->cub3d_data.current_surface)
		ft_error_handling(9, NULL, config);
	config->cub3d_data.img = mlx_texture_to_image(config->cub3d_data.mlx,
			config->cub3d_data.current_surface);
	if (!config->cub3d_data.img)
		ft_error_handling(23, NULL, config);
	return (surface);
}
	*/



//for minimap - here we should use the MINIMAP drawing surface
void drawLine(t_color color, mlx_image_t *minimap_surface, t_vector2 start, t_vector2 end)
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
        // Add bounds checking
        if (start.x >= 0 && start.x < minimap_surface->width && 
            start.y >= 0 && start.y < minimap_surface->height)
        {
            putPixel(color, minimap_surface, (int)start.x, (int)start.y);
        }
        start = addvectors(start, step);
        i++;
    }
}
/*
//this function fills the top half of the surface with the ceiling color
void fillCeiling(t_gamedata *config){
	const t_color color = *config->ceiling;

	for (int y = 0; y < config->window_height / 2; y++){
		for (int x = 0; x < config->window_width; x++){
			putPixel(color, config->cub3d_data.current_surface, x, y);
		}
	}
}
*/
/**
 * @brief this function fills the bottom half of the surface with the floor color
 * as y = 0 is at the top and y = window_height is at the bottom

void	fillFloor(t_gamedata *config)
{
	t_color	color;

	color = *config->floor;
	for (int y = config->window_height / 2; y < config->window_height; y++){
		for (int x = 0; x < config->window_width; x++){
			putPixel(color, config->cub3d_data.current_surface, x, y);
		}
	}
}
*/
