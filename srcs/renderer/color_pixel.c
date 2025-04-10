/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:10 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 19:48:41 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief function that draws a pixel of
 * parameter color at position x,y on the surface
 */

void	putpixel(t_color color, mlx_image_t *img, uint32_t x, uint32_t y)
{
	int			pixel_index;

	pixel_index = 0;
	if (x < img->width && y < img->height)
	{
		pixel_index = (y * img->width + x) * sizeof(int32_t);
		img->pixels[pixel_index] = color.red;
		img->pixels[pixel_index + 1] = color.green;
		img->pixels[pixel_index + 2] = color.blue;
		img->pixels[pixel_index + 3] = color.alpha;
	}
}
