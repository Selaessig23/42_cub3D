/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:13 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 18:39:24 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	int				fd;
	t_gamedata		*config;

	fd = 0;
	config = NULL;
	if (argc == 2)
	{
		if (!ft_extension_check(argv[1]))
			fd = ft_access_check(argv[1]);
		config = ft_initiate_data(fd);
		ft_freeing_support(fd, NULL);
		ft_init_mlx(config);
		mlx_resize_hook(config->cub3d_data.mlx, resize, config);
		mlx_key_hook(config->cub3d_data.mlx, key_handler, config);
		mlx_loop_hook(config->cub3d_data.mlx, render, config);
		mlx_loop(config->cub3d_data.mlx);
		ft_cleanup(config, false);
	}
	else
		ft_error_handling(0, NULL, NULL);
	return (0);
}
