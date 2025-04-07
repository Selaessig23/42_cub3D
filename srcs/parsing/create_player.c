/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:28:45 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/07 10:28:52 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * in this file the map is checked for valid player information
 * if valid, the player's position is set
 * if invalid (no player, more than one player) program 
 * exits and returns error message
 */

/**
 * @brief function to set players direction
 * (helper function for ft_set_player)
 */
static t_vector2	ft_set_players_dir(t_gamedata **p_config, char dir)
{
	t_vector2	player_dir;

	if (dir == 'N')
	{
		player_dir.x = 0;
		player_dir.y = 1;
	}
	else if (dir == 'E')
	{
		player_dir.x = -1;
		player_dir.y = 0;
	}
	else if (dir == 'S')
	{
		player_dir.x = 0;
		player_dir.y = -1;
	}
	else if (dir == 'W')
	{
		player_dir.x = 1;
		player_dir.y = 0;
	}
	return (player_dir);
}

/**
 * @brief function to set the players position in the grid
 * and checks for players direction
 * 
 */
static void	ft_set_player(t_gamedata **p_config, int x, int y, char dir)
{
	t_gamedata	*config;
	t_player	p;
	t_vector2	player_pos;

	config = *p_config;
	config->player.pos.x = (double)x;
	config->player.pos.y = (double)y;
	config->player.dir = ft_set_players_dir(p_config, dir);
	config->player.fov = 90;
	// printf("x = %i, x_config = %f\n", x, config->player.pos.x);
	// printf("y = %i, y_config = %f\n", y, config->player.pos.y);
	// printf("x_config.dir = %f\n", config->player.dir.x);
	// printf("y_config.dir = %f\n", config->player.dir.y);
}

/**
 * @brief function that checks if a player already exists,
 * if yes it exists the programm and returns error message
 * otherwiese it returns 1
 */
static int	ft_check_for_player_duplicates(t_gamedata *config, int fd)
{
	t_player	p;
	t_vector2	player_pos;


	p = config->player;
	player_pos = p.pos;
	if (player_pos.x && player_pos.y)
	{
		close (fd);
		ft_error_handling(12, NULL, config);
	}
	return (1);
}

/**
 * @brief function that checks if there is a 
 * player AND if there is only one player
 * 
 * integrated a ternary (conditional) operator
 * to save space for return value
 * (conditions automatically return 1 for true and 0 for false)
 */
int	ft_player_check(t_gamedata *config, int fd)
{
	int		p;
	int		x;
	int		y;

	p = 0;
	y = 0;
	x = 0;
	while (config->map[y])
	{
		x = 0;
		while (config->map[y][x])
		{
			if (config->map[y][x] == 'N' || config->map[y][x] == 'S'
				|| config->map[y][x] == 'W' || config->map[y][x] == 'E')
			{
				p = ft_check_for_player_duplicates(config, fd);
				ft_set_player(&config, x, y, config->map[y][x]);
			}
			x += 1;
		}
		y += 1;
	}
	return (p == 1);
}
