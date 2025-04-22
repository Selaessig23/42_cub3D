/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:58:15 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/22 17:07:46 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_player_rotation(mlx_key_data_t keydata, t_gamedata *config)
{
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, ROTATION_SPEED));
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, -ROTATION_SPEED));
}
