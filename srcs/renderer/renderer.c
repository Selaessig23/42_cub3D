/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:05 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/22 17:13:21 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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


