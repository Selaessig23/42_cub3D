/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locomotion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:48 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/27 15:00:27 by mstracke         ###   ########.fr       */
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
 * 
 * @param up if true player needs to move up, if false down
 */
static void	ft_player_move_updown(mlx_key_data_t keydata, 
	t_gamedata *config, float move_speed, bool up)
{
	t_vector2	move_vec;
	t_vector2	new_pos;
	t_vector2	test_pos_x;
	t_vector2	test_pos_y;

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
	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		config->player.pos.x = new_pos.x;
	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		config->player.pos.y = new_pos.y;
}

/**
 * @brief key handler for right/left movements of player
 * 
 * @param right if true, player needs to move right, if false left
 */
static void	ft_player_move_rl(mlx_key_data_t keydata, 
	t_gamedata *config, float move_speed, bool right)
{
	t_vector2	strafe_dir;	
	t_vector2	new_pos;
	t_vector2	test_pos_x;
	t_vector2	test_pos_y;

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
	new_pos = addvectors(config->player.pos, strafe_dir);
	test_pos_x.x = new_pos.x;
	test_pos_x.y = config->player.pos.y;
	test_pos_y.x = config->player.pos.x;
	test_pos_y.y = new_pos.y;
	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		config->player.pos.x = new_pos.x;
	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		config->player.pos.y = new_pos.y;

		//t_vector2 strafe_dir = {-config->player.dir.y, config->player.dir.x};
		// 	strafe_dir = normalizevector(strafe_dir);
		// 	strafe_dir = multiplyvector(strafe_dir, move_speed);
		// 	t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);
		// 	t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		// 	t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
		// 	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		// 		config->player.pos.x = new_pos.x;
		// 	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
		// 		config->player.pos.y = new_pos.y;
}

void	ft_player_movement(mlx_key_data_t keydata, t_gamedata *config)
{
	float		move_speed;

	move_speed = 0.5; // Smaller value for more precise movement
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		ft_player_move_updown(keydata, config, move_speed, true);
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		ft_player_move_updown(keydata, config, move_speed, false);
	else if (keydata.key == MLX_KEY_A)
		ft_player_move_rl(keydata, config, move_speed, false);
	else if (keydata.key == MLX_KEY_D)
		ft_player_move_rl(keydata, config, move_speed, true);
}

void	ft_player_rotation(mlx_key_data_t keydata, t_gamedata *config)
{
	float		rotation_speed;

	rotation_speed = 0.15; // Smaller value for more precise rotation
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, rotation_speed));
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E)
		config->player.dir = normalizevector
			(rotatevector(config->player.dir, -rotation_speed));
}

/**
 * @brief handler function for mlx_key_hook
 * 
 * TODO: split into several functions
 * TODO: free everything in case of ESCAPE
 * 
 * @param A user-defined pointer that can store extra data 
 * (in this case: the struct t_gamedata with game-config's data).
 */
/*
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_gamedata	*config;
	float		move_speed;
	float		rotation_speed;

	config = (t_gamedata *)param;
	move_speed = 0.5; // Smaller value for more precise movement
	rotation_speed = 0.15; // Smaller value for more precise rotation
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		// mlx_close_window(config->cub3d_data.mlx);
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


	// if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W  ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// {
	// 	t_vector2 move_vec = normalizevector(config->player.dir);
	// 	move_vec = multiplyvector(move_vec, move_speed);
	// 	t_vector2 new_pos = addvectors(config->player.pos, move_vec);
	// 	t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
	// 	t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
	// 	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.x = new_pos.x;
	// 	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.y = new_pos.y;
	// }
	// if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// {
	// 	t_vector2 move_vec = normalizevector(config->player.dir);
	// 	move_vec = multiplyvector(move_vec, -move_speed); // Negative for backward
	// 	t_vector2 new_pos = addvectors(config->player.pos, move_vec);
	// 	t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
	// 	t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
	// 	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.x = new_pos.x;
	// 	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.y = new_pos.y;
	// }
	// if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// {
	// 	t_vector2 strafe_dir = {-config->player.dir.y, config->player.dir.x};
	// 	strafe_dir = normalizevector(strafe_dir);
	// 	strafe_dir = multiplyvector(strafe_dir, move_speed);
	// 	t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);
	// 	t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
	// 	t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
	// 	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.x = new_pos.x;
	// 	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.y = new_pos.y;
	// }
	// if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// {
	// 	t_vector2 strafe_dir = {config->player.dir.y, -config->player.dir.x};
	// 	strafe_dir = normalizevector(strafe_dir);
	// 	strafe_dir = multiplyvector(strafe_dir, move_speed);
	// 	t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);
	// 	t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
	// 	t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
	// 	if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.x = new_pos.x;
	// 	if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
	// 	config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
	// 		config->player.pos.y = new_pos.y;
	// }
	// if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
	// 	&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// 	config->player.dir = normalizevector(
	// 			rotatevector(config->player.dir, rotation_speed));
	// if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// {
	// 	config->player.dir = normalizevector(rotatevector(config->player.dir, -rotation_speed));
	// }
	if ((keydata.key == MLX_KEY_TAB) && (keydata.action == MLX_PRESS))
	{
		config->show_minimap = !config->show_minimap;
		printf("show minimap: %i\n", config->show_minimap);
	}
}
*/