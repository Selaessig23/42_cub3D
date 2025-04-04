/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:13 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/03 16:58:42 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;
	int				map_x;
	int				map_y;
	char			**map;

	fd = 0;
	config = NULL;
	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		config = ft_initiate_data(fd);
		close(fd);
        //without this we can floating point problems - 
		//i think it is the equivalent of using a bigger collision box
		//move to parsing-part
        config->player.pos.x += 0.1;
        config->player.pos.y += 0.1;
		//just for testing reasons
		ft_testprint(config);
		//initiate mlx-data with game-config-data (validated)
		ft_init_mlx(config);
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
		// ft_free_config(config);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}
