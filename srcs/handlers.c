/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:05 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 16:39:19 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

/**
 * DESCRIPTION:
 * in this file all the handler-function are listed
 * 1) resize from mlx_resize_hook-call to handle resizing of window
 * 2) key_handler from mlx_key_hook-call to handle keyboard input
 * 3) render from mlx_loop_hook-call to organise the image-creation (rendering)
 * during game (loop)
 */

/**
 * @brief handler function for mlx_loop_hook
 * it renders each pixel of the image
 * 
 * @param param A user-defined pointer that can store extra data 
 * (in this case: the struct t_gamedata with game-config's data).
 */
void	render(void *param)
{
	t_gamedata	*config;

	config = (t_gamedata *)param;
	fill_lower_half(config->cub3d_data.img, *config->floor);
	fill_upper_half(config->cub3d_data.img, *config->ceiling);
	cast_ray_and_draw_wall(config->map, config->cub3d_data.img, config);
	if (config->show_minimap)
		draw_minimap(config);
}

/**
 * @brief handler function for mlx_key_hook
 * 
 * for move_speed and rotation_speed a smaller value would cause
 * more precise movement / rotation
 * 
 * @param param A user-defined pointer that can store extra data 
 * (in this case: the struct t_gamedata with game-config's data).
 */
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_gamedata	*config;

	config = (t_gamedata *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_cleanup(config, false);
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_D)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_player_movement(keydata, config);
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		ft_player_rotation(keydata, config);
	if ((keydata.key == MLX_KEY_TAB) && (keydata.action == MLX_PRESS))
	{
		ft_minimap_switcher(config);
	}
}

/**
 * @brief handler function for mlx_resize_hook. 
 * It tries to resize the image after resizing the window.
 * 
 * TODO: The old image seems to remain unchanged 
 * and should be maybe manually freed if no longer needed.
 * 
 * @param with new width after resizing
 * @param height new height after resizing
 * @param param A user-defined pointer that can store extra data 
 * (in this case: the struct t_gamedata with game-config's data).
 */
void	resize(int width, int height, void *param)
{
	t_gamedata	*config;

	config = (t_gamedata *)param;
	if (!mlx_resize_image(config->cub3d_data.img, width, height))
		ft_error_handling(25, NULL, config);
}
