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

/**
 * DESCRIPTION:
 * file that coordinates the movement and rotation requests
 * from keyboard usage (organised via key_handler of mlx_key_hook-function)
 */

/**
 * @brief key handler for up/down movements of player
 * if there is a wall (= 1 or a space) on x or y,
 * player keeps current position on blocked x / y, while moving forward
 * in free direction (floor = 0)
 *
 * @param up if true player needs to move up, if false down
 */
static void	ft_player_move_updown(t_gamedata *config, double move_speed, bool up)
{
	const double		player_radius = 0.1;
	t_vector2		move_vec;
	t_vector2		new_pos;
	t_vector2		test_pos_x;
	t_vector2		test_pos_y;

	move_vec = normalizevector(config->player.dir);
	if (up == true)
		move_vec = multiplyvector(move_vec, move_speed);
	else
		move_vec = multiplyvector(move_vec, -move_speed);
	new_pos = addvectors(config->player.pos, move_vec);
	test_pos_x.x = new_pos.x;
	test_pos_x.y = config->player.pos.y;
	test_pos_y.x = config->player.pos.x;
	test_pos_y.y = new_pos.y;
	if (!ft_player_collision(config, test_pos_x, player_radius))
		config->player.pos.x = new_pos.x;
	if (!ft_player_collision(config, test_pos_y, player_radius))
		config->player.pos.y = new_pos.y;
}

/**
 * @brief helper function for player_move_rl to define strafe_dir
 */
t_vector2	ft_strafe_dir(t_gamedata *config, double move_speed, bool right)
{
	t_vector2	strafe_dir;

	if (right == true)
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
	strafe_dir = multiplyvector(strafe_dir, move_speed);
	return (strafe_dir);
}

static void	ft_player_move_rl(t_gamedata *config, double move_speed, bool right)
{
	t_vector2		strafe_dir;
	t_vector2		new_pos;
	t_vector2		test_pos_x;
	t_vector2		test_pos_y;
	const double	player_radius = 0.3;

	strafe_dir = ft_strafe_dir(config, move_speed, right);
	new_pos = addvectors(config->player.pos, strafe_dir);
	test_pos_x.x = new_pos.x;
	test_pos_x.y = config->player.pos.y;
	test_pos_y.x = config->player.pos.x;
	test_pos_y.y = new_pos.y;
	if (!ft_player_collision(config, test_pos_x, player_radius))
		config->player.pos.x = new_pos.x;
	if (!ft_player_collision(config, test_pos_y, player_radius))
		config->player.pos.y = new_pos.y;
}

/**
 * @brief function to differentiate the direction of movement
 * and define the speed of the movement
 *
 * move_speed = 0.5; --> Smaller value for more precise movement
 *
 */
void	ft_player_movement(mlx_key_data_t keydata, t_gamedata *config)
{
	double		move_speed;

	move_speed = 0.5;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_player_move_updown(config, move_speed, true);
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		ft_player_move_updown(config, move_speed, false);
	else if (keydata.key == MLX_KEY_A)
		ft_player_move_rl(config, move_speed, false);
	else if (keydata.key == MLX_KEY_D)
		ft_player_move_rl(config, move_speed, true);
}

/**
 * @brief function that organises the rotation in case of key input
 * and defines the rotation speed
 *
 * rotation_speed = 0.15; --> Smaller value for more precise rotation
 *
 */
void	ft_player_rotation(mlx_key_data_t keydata, t_gamedata *config)
{
	double		rotation_speed;

	rotation_speed = 0.15;
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, rotation_speed));
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, -rotation_speed));
}
