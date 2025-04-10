/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:48:11 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/10 19:53:55 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_testprint_maparray(char **map_arr)
{
	int		i;

	i = 0;
	while (map_arr[i])
	{
		printf("line %i of map: %s\n", i, map_arr[i]);
		i += 1;
	}
}

/**
 * @brief test function to print the input of game config struct
 */
void	ft_testprint(t_gamedata *config)
{
	t_color	*floor_print;
	t_color	*ceiling_print;

	floor_print = config->floor;
	ceiling_print = config->ceiling;
	ft_printf("\n---------------------------------"
		"-------------------------------\n");
	ft_printf("TEST: Print input of struct game_config\n");
	ft_printf("fd_north: %s\n", config->t_north);
	ft_printf("fd_south: %s\n", config->t_south);
	ft_printf("fd_east: %s\n", config->t_east);
	ft_printf("fd_west: %s\n", config->t_west);
	ft_printf("ceiling red: %i\n", ceiling_print->red);
	ft_printf("ceiling green: %i\n", ceiling_print->green);
	ft_printf("ceiling blue: %i\n", ceiling_print->blue);
	ft_printf("floor red: %i\n", floor_print->red);
	ft_printf("floor green: %i\n", floor_print->green);
	ft_printf("floor blue: %i\n", floor_print->blue);
	printf("Player pos x = %f\n", config->player.pos.x);
	printf("Player pos y = %f\n", config->player.pos.y);
	printf("Player dir x = %f\n", config->player.dir.x);
	printf("Player dir y = %f\n", config->player.dir.y);
	ft_printf("Player fov: %i\n", config->player.fov);
	ft_testprint_maparray(config->map);
	ft_printf("-----------------------\n");
}
