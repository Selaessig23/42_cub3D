
#include "cub3d.h"

/**
 * @brief function that draws a pixel of 
 * parameter color at position x,y on the surface
 */
void	putPixel(t_color color, mlx_image_t *img, uint32_t x, uint32_t y)
{
	int			pixel_index;

	pixel_index = 0;
	// printf("red: %i, green: %i, blue: %i, alpha: %i\n", color.red, color.green, color.blue, color.alpha);
	if (x < img->width && y < img->height)
	{
		// pixel_index = (y * img->width + x) * 4;
		pixel_index = (y * img->width + x) * sizeof(int32_t);
		img->pixels[pixel_index] = color.red;
		img->pixels[pixel_index + 1] = color.green;
		img->pixels[pixel_index + 2] = color.blue;
		img->pixels[pixel_index + 3] = color.alpha;
	}
}
