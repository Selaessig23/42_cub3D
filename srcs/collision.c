/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:21:56 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 23:34:42 by pvasilan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "cub3d.h"

static	bool	ft_is_wall_collision(t_gamedata *config, t_vector2 pos)
{
	return (config->map[(int)pos.y][(int)pos.x] == '1'
		|| config->map[(int)pos.y][(int)pos.x] == ' ');
}

bool	ft_player_collision(t_gamedata *config,
		t_vector2 pos, float player_radius)
{
	t_vector2	collision_points[4];
	int			i;

	collision_points[0].x = pos.x;
	collision_points[0].y = pos.y - player_radius;
	collision_points[1].x = pos.x + player_radius;
	collision_points[1].y = pos.y;
	collision_points[2].x = pos.x;
	collision_points[2].y = pos.y + player_radius;
	collision_points[3].x = pos.x - player_radius;
	collision_points[3].y = pos.y;
	i = 0;
	while (i < 4)
	{
		if (ft_is_wall_collision(config, collision_points[i]))
			return (true);
		i++;
	}
	return (false);
}
