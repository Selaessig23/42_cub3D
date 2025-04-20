/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locomotion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:48 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/11 14:56:36 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define PLAYER_RADIUS 0.2
#define MOVE_SPEED 0.3
#define ROTATION_SPEED 0.1

static bool	ft_is_valid_position(t_gamedata *config, t_vector2 pos)
{
	return (!ft_player_collision(config, pos, PLAYER_RADIUS));
}

static void	ft_player_move_updown(t_gamedata *config, bool up)
{
	t_vector2	move_vec;
	t_vector2	new_pos;

	move_vec = normalizevector(config->player.dir);
	if (up)
		move_vec = multiplyvector(move_vec, MOVE_SPEED);
	else
		move_vec = multiplyvector(move_vec, -MOVE_SPEED);
	
	new_pos = addvectors(config->player.pos, move_vec);
	if (ft_is_valid_position(config, new_pos))
		config->player.pos = new_pos;
}

t_vector2	ft_strafe_dir(t_gamedata *config, bool right)
{
	t_vector2	strafe_dir;

	if (right)
	{
		strafe_dir.x = config->player.dir.y;
		strafe_dir.y = -config->player.dir.x;
	}
	else
	{
		strafe_dir.x = -config->player.dir.y;
		strafe_dir.y = config->player.dir.x;
	}
	strafe_dir = normalizevector(strafe_dir);
	strafe_dir = multiplyvector(strafe_dir, MOVE_SPEED);
	return (strafe_dir);
}

static void	ft_player_move_rl(t_gamedata *config, bool right)
{
	t_vector2	strafe_dir;
	t_vector2	new_pos;

	strafe_dir = ft_strafe_dir(config, right);
	new_pos = addvectors(config->player.pos, strafe_dir);
	if (ft_is_valid_position(config, new_pos))
		config->player.pos = new_pos;
}

void	ft_player_movement(mlx_key_data_t keydata, t_gamedata *config)
{
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_player_move_updown(config, true);
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		ft_player_move_updown(config, false);
	else if (keydata.key == MLX_KEY_A)
		ft_player_move_rl(config, false);
	else if (keydata.key == MLX_KEY_D)
		ft_player_move_rl(config, true);
}

void	ft_player_rotation(mlx_key_data_t keydata, t_gamedata *config)
{
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, ROTATION_SPEED));
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, -ROTATION_SPEED));
}
