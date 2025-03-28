/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:13 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/28 15:46:25 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
mlx_image_t	*create_square(mlx_t *mlx, uint32_t size, t_color color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	// Fill the image with the specified color
	for (uint32_t y = 0; y < size; y++)
	{
		for (uint32_t x = 0; x < size; x++)
		{
			putPixel(color, img, x, y );
		}
	}
	return (img);
}
*/

/*
mlx_image_t	*create_transparent_pattern(mlx_t *mlx, uint32_t size, uint32_t color)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
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
	return (img);
}
*/

/**
 * 
 
void	copy_texture(mlx_image_t *img, mlx_image_t *texture, uint32_t x, uint32_t y)
{
	 for (uint32_t i = 0; i < texture->height; i++)
	 {

			t_color color = {0xFFAAAA11};


			putPixel(color, img, x, y + i);
		//uint32_t color = texture->pixels[i * texture->width + texture->width / 2];
	 }
}
*/

int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;
	int				map_x;
	int				map_y;
	char			**map;
	// int				img_instance;
	// int				minimap_instance;

	fd = 0;
	config = NULL;
	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		config = ft_initiate_data(fd);
		close(fd);
        //without this we can floating point problems - i think it is the equivalent of using a bigger collision box
        config->player.pos.x += 0.1;
        config->player.pos.y += 0.1;


		// if (!config->player.pos.x)
		// 	config->player.pos.x = 9;
		// if (!config->player.pos.y)
		// 	config->player.pos.y = 5;
		// if (!config->player.dir.x)
		// 	config->player.dir.x = -1;
		// if (!config->player.dir.y)
		// 	config->player.dir.y = 0;
		// if (!config->player.fov)
		// 	config->player.fov = 90;

		//just for testing reasons
		ft_testprint(config);

		//initiate mlx-data with game-config-data (validated)
		ft_init_mlx(config);
		// if (!(config->cub3d_data.mlx = mlx_init(640, 480, "cub3Deluxe", true)))
		// 	ft_error_handling(20, NULL, config);
		// config->cub3d_data.img = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		// if (!config->cub3d_data.img)
		// 	ft_error_handling(21, NULL, config);
		// config->cub3d_data.minimap_surface = mlx_new_image(config->cub3d_data.mlx, 640, 480);
		// if (!config->cub3d_data.minimap_surface)	
		// 	ft_error_handling(21, NULL, config);
		// load_wall_textures(config);
		// img_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.img, 0, 0);
		// if (img_instance < 0)
		// 	ft_error_handling(22, NULL, config);
		// //set the depth of each image (z-index), higher values appear above lower ones
		// mlx_set_instance_depth(&config->cub3d_data.img->instances[img_instance], 0);
		// minimap_instance = mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.minimap_surface, 0, 0);
		// if (minimap_instance < 0)
		// 	ft_error_handling(22, NULL, config);
		// //depth of minimap is higher than cub3D-image
		// mlx_set_instance_depth(&config->cub3d_data.minimap_surface->instances[minimap_instance], 1);

		
		//set size of map -> maybe move to parsing part, if required,
		//seems to not have any specific use
		// map = config->map;
		// map_x = ft_strlen(map[0]);
		// map_y = ft_arrlen(map);

		//adapt image size in case of window resizing
		mlx_resize_hook(config->cub3d_data.mlx, resize, config);
		//handling of keyboard use
		mlx_key_hook(config->cub3d_data.mlx, key_handler, config);
		//raycasting-part
		mlx_loop_hook(config->cub3d_data.mlx, render, config);
		//game loop
		mlx_loop(config->cub3d_data.mlx);
		//cleaning up
		ft_cleanup(config, false);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}
