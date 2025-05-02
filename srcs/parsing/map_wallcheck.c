/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wallcheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:16:06 by mstracke          #+#    #+#             */
/*   Updated: 2025/05/02 13:11:53 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION: 
 * file to check if the map is closed/surrounded by walls, 
 * if not the program must return an errormessage and exit.
 * 
 * it checks each side of the map for walls. if there is
 * a space it calls the function ft_check_cave which checks 
 * if the space (cave) is surrounded by walls
 * 
 * check what happens if map starts with 0
 */

int	ft_west_check(t_gamedata *config, int fd, char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i] && map[i][j])
	{
		j = 0;
		if (map[i][j] == ' ' && !ft_check_cave(index, i, j, 'W'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else if (map[i][j] == '1' || map[i][j] == ' ')
			i += 1;
		else
		{
			ft_free(index);
			close(fd);
			ft_error_handling(17, ft_strdup("WEST"), config);
		}
		ft_refill_map(index, map);
	}
	return (1);
}

int	ft_east_check(t_gamedata *config, int fd, char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(map[i]) - 1;
	while (map[i] && map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_cave(index, i, j, 'E'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else if (map[i][j] == '1' || map[i][j] == ' ')
			i += 1;
		else
		{
			ft_free(index);
			close(fd);
			ft_error_handling(17, ft_strdup("EAST"), config);
		}
		if (map[i])
			j = ft_strlen(map[i]) - 1;
		ft_refill_map(index, map);
	}
	return (1);
}

int	ft_south_check(t_gamedata *config, int fd, char **map, char **index)
{
	int		i;
	int		j;

	i = ft_arrlen(map) - 1;
	j = ft_strlen(map[i]) - 1;
	while (j >= 0)
	{
		if (map[i][j] == ' ' && !ft_check_cave(index, i, j, 'S'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else if (map[i][j] == '1' || map[i][j] == ' ')
			j -= 1;
		else
		{
			ft_free(index);
			close(fd);
			ft_error_handling(17, ft_strdup("SOUTH"), config);
		}
		ft_refill_map(index, map);
	}
	return (1);
}

int	ft_north_check(t_gamedata *config, int fd, char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_cave(index, i, j, 'N'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else if (map[i][j] == '1' || map[i][j] == ' ')
			j += 1;
		else
		{
			ft_free(index);
			close(fd);
			ft_error_handling(17, ft_strdup("NORTH"), config);
		}
		ft_refill_map(index, map);
	}
	return (1);
}

/**
 * @brief function to check if the map is surrounded by walls
 * it checks each side of the map for walls
 * 
 * ???north and west check has to be fixed, 
 * still error prone in case of caves???
 */
int	ft_wall_check(t_gamedata *config, int fd, char **index)
{
	if (!ft_east_check(config, fd, config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("EAST"), config);
	}
	else if (!ft_north_check(config, fd, config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("NORTH"), config);
	}
	else if (!ft_west_check(config, fd, config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("WEST"), config);
	}
	else if (!ft_south_check(config, fd, config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("SOUTH"), config);
	}
	return (1);
}
