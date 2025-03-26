/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:59:48 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/15 19:01:38 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"




void	resize(int width, int height, void *param)
{
	t_gamedata	*config;

	config = (t_gamedata *)param;
	mlx_resize_image(config->cub3d_data.img, width, height);
}
void	key_handler(mlx_key_data_t keydata, void *param)
{
	t_gamedata *config = (t_gamedata *)param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(config->cub3d_data.mlx);
	float move_speed = 0.5;  // Smaller value for more precise movement
	float rotation_speed = 0.15;  // Smaller value for more precise rotation
	if ((keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W  ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		t_vector2 move_vec = normalizevector(config->player.dir);
		move_vec = multiplyvector(move_vec, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, move_vec);
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
		if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.x = new_pos.x;
		if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.y = new_pos.y;
	}
	if ((keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		t_vector2 move_vec = normalizevector(config->player.dir);
		move_vec = multiplyvector(move_vec, -move_speed); // Negative for backward
		t_vector2 new_pos = addvectors(config->player.pos, move_vec);
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
		if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.x = new_pos.x;
		if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.y = new_pos.y;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		t_vector2 strafe_dir = {-config->player.dir.y, config->player.dir.x};
		strafe_dir = normalizevector(strafe_dir);
		strafe_dir = multiplyvector(strafe_dir, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
		if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.x = new_pos.x;
		if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.y = new_pos.y;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		t_vector2 strafe_dir = {config->player.dir.y, -config->player.dir.x};
		strafe_dir = normalizevector(strafe_dir);
		strafe_dir = multiplyvector(strafe_dir, move_speed);
		t_vector2 new_pos = addvectors(config->player.pos, strafe_dir);
		t_vector2 test_pos_x = {new_pos.x, config->player.pos.y};
		t_vector2 test_pos_y = {config->player.pos.x, new_pos.y};
		if (config->map[(int)test_pos_x.y][(int)test_pos_x.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.x = new_pos.x;
		if (config->map[(int)test_pos_y.y][(int)test_pos_y.x] != '1' &&
		config->map[(int)test_pos_x.y][(int)test_pos_x.x] != ' ')
			config->player.pos.y = new_pos.y;
	}
	if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_Q)
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		config->player.dir = normalizevector(
				rotatevector(config->player.dir, rotation_speed));
	if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_E ) && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		config->player.dir = normalizevector(rotatevector(config->player.dir, -rotation_speed));
	}
	if ((keydata.key == MLX_KEY_TAB) && (keydata.action == MLX_PRESS))
	{
		config->show_minimap = !config->show_minimap;
		printf("show minimap: %i\n", config->show_minimap);
	}
}
