/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:09 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/04 11:21:02 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void start_window()
// {
// }


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
		// printf("test x\n");
		if (!(config->cub3d_data.img = mlx_new_image(config->cub3d_data.mlx, 540, 380)))
		{
			mlx_close_window(config->cub3d_data.mlx);
			ft_error_handling(21, NULL, config);
		}
		createSurface(config);
		if (mlx_image_to_window(config->cub3d_data.mlx, config->cub3d_data.img, 0, 0) == -1)
		{
			mlx_close_window(config->cub3d_data.mlx);
			ft_error_handling(22, NULL, config);
		}
		// fillCeiling(config);
		// fillFloor(config);
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
