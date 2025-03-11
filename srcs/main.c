/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:09 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/11 20:10:08 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void start_window()
// {
// }

#define WIDTH 800
#define HEIGHT 600

// Helper function to create a square with a specific color and alpha
mlx_image_t *create_square(mlx_t *mlx, uint32_t size, t_color color)
{
    mlx_image_t *img = mlx_new_image(mlx, size, size);
    if (!img)
        return NULL;

    // Fill the image with the specified color
    for (uint32_t y = 0; y < size; y++)
    {
        for (uint32_t x = 0; x < size; x++)
        {
            putPixel(color, img, x, y );
        }
    }
    return img;
}

// Function to create a checkerboard pattern with transparency
mlx_image_t *create_transparent_pattern(mlx_t *mlx, uint32_t size, uint32_t color)
{
    mlx_image_t *img = mlx_new_image(mlx, size, size);
    if (!img)
        return NULL;

    // Create a checkerboard pattern with some pixels fully transparent
    for (uint32_t y = 0; y < size; y++)
    {
        for (uint32_t x = 0; x < size; x++)
        {
            // Make a checkerboard pattern by making some pixels transparent
            if ((x / 10 + y / 10) % 2 == 0)
                mlx_put_pixel(img, x, y, color);
            else
                mlx_put_pixel(img, x, y, 0x00000000); // Fully transparent
        }
    }
    return img;
}

int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;

	fd = 0;
	config = NULL;
	//config->map = create_empty_map();


	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		// dprintf(1, "correct no of arguments and correct extension "
		// 	"for gaming fun, fd: %i\n", fd);

		config = ft_initiate_data(fd);
		ft_testprint(config);
		if (!(config->cub3d_data.mlx = mlx_init(640, 480, "Markus' and Pavlos' cub3D", true)))
			ft_error_handling(20, NULL, config);
		t_color color = {0xFF0000FF}; // Blue with full opacity
		t_color color2 = {0x66FF0000}; // Green with full opacity

		mlx_image_t *background = create_square(config->cub3d_data.mlx , 200, color); // Blue with full opacity
		mlx_image_t *foreground = create_square(config->cub3d_data.mlx, 200, color2);
		int bg_instance = mlx_image_to_window(config->cub3d_data.mlx, background, 200, 200);
		int fg_instance = mlx_image_to_window(config->cub3d_data.mlx, foreground, 250, 250);
		mlx_set_instance_depth(&background->instances[bg_instance], 0);
    	mlx_set_instance_depth(&foreground->instances[fg_instance], 1);

		printf("color1 red: %i, green: %i, blue: %i, alpha: %i\n", color.red, color.green, color.blue, color.alpha);
		printf("color2 red: %i, green: %i, blue: %i, alpha: %i\n", color2.red, color2.green, color2.blue, color2.alpha);

		// // printf("test x\n");
		// if (!(config->cub3d_data.img = mlx_new_image(config->cub3d_data.mlx, 540, 380)))
		// {
		// 	mlx_close_window(config->cub3d_data.mlx);
		// 	ft_error_handling(21, NULL, config);
		// }
		// createSurface(config);
		// if (mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.img, 0, 0) == -1)
		// {
		// 	mlx_close_window(config->cub3d_data.mlx);
		// 	ft_error_handling(22, NULL, config);
		// }
		// // fillCeiling(config);
		// // fillFloor(config);
		mlx_loop(config->cub3d_data.mlx);
		sleep(3);
		close (fd);
		//mlx_close_window(config->cub3d_data.mlx);
		mlx_terminate(config->cub3d_data.mlx);
		ft_free_config(config);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}
