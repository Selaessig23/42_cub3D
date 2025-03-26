/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:05 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/26 13:16:46 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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


