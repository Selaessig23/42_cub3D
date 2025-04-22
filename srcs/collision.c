/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:21:56 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/22 17:08:28 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define COLLISION_EPSILON 0.01

static	bool	ft_is_wall_collision(t_gamedata *config, t_vector2 pos)
{
	return (config->map[(int)pos.y][(int)pos.x] == '1'
		|| config->map[(int)pos.y][(int)pos.x] == ' ');
}

bool	ft_player_collision(t_gamedata *config,
		t_vector2 pos, double player_radius)
{
	t_vector2	collision_points[9];
	int			i;
	double		angle;

	collision_points[0] = pos;
	i = 0;
	while (i < 9)
	{
		angle = (i - 1) * M_PI_4; 
		collision_points[i].x = pos.x + cos(angle) * player_radius;
		collision_points[i].y = pos.y + sin(angle) * player_radius;
		i++;
	}
	i = 0;
	while (i < 9)
	{
		if (ft_is_wall_collision(config, collision_points[i]))
			return (true);
		i++;
	}
	return (false);
}
