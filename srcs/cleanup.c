/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:32:05 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/08 10:32:24 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRPIPTION:
 * file that organises the cleanup in case of an error or normal cease
 * 
 */

/**
 * @brief function to delete the images that have been created for
 * game execution
 */
static void	delete_images(t_gamedata *config)
{
	if (config->cub3d_data.img)
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.img);
	if (config->cub3d_data.minimap_surface)
		mlx_delete_image(config->cub3d_data.mlx,
			config->cub3d_data.minimap_surface);
	if (config->cub3d_data.east)
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.east);
	if (config->cub3d_data.west)
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.west);
	if (config->cub3d_data.north)
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.north);
	if (config->cub3d_data.south)
		mlx_delete_image(config->cub3d_data.mlx, config->cub3d_data.south);
}

/**
 * @brief function to organise freeing and closing
 * in case there was an error, config-struct will be freed in
 * function ft_error_handling
 */
void	ft_cleanup(t_gamedata *config, bool error)
{
	delete_images(config);
	mlx_close_window(config->cub3d_data.mlx);
	mlx_terminate(config->cub3d_data.mlx);
	if (error == 0)
	{
		ft_free_config(config);
		exit (0);
	}
}
