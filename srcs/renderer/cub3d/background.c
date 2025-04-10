/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:35:57 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 19:47:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * in this file the background of the game gets colored.
 * background in this case simply means that the img is devided
 * into two parts for floor and ceiling color.
 * This serves as a first layer. Raycasting of wall-textures simply
 * oferwrites the background color (~2nd layer).
 *
 * Possibility to improve this handling:
 * Instead of drawing floors first, render floor pixels row-by-row,
 * stopping early if a wall pixel will overwrite them.
 * This would reduce overdraw.
 */

/**
 * @brief function to define floor-color for each pixel of
 * lower half
 * as y = 0 is at the top and y = window_height is at the bottom
 *
 */
void	fill_lower_half(mlx_image_t *img, t_color color)
{
	uint32_t	y;
	uint32_t	x;

	y = (img->height / 2);
	x = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			putpixel(color, img, x, y);
			x += 1;
		}
		y += 1;
	}
}

/**
 * @brief function to define ceiling-color for each pixel of
 * upper half
 *
 */
void	fill_upper_half(mlx_image_t *img, t_color color)
{
	uint32_t	y;
	uint32_t	x;

	y = 0;
	x = 0;
	while (y < (img->height / 2))
	{
		x = 0;
		while (x < img->width)
		{
			putpixel(color, img, x, y);
			x += 1;
		}
		y += 1;
	}
}
