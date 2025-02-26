#include "cub3d.h"

/**
 * DESCRIPTION: 
 * file to check if the map is closed/surrounded by walls, 
 * if not the program must returns an errormessage and exits.
 * 
 * check what happens if map starts with 0
 */

int	ft_west_check(char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i] && map[i][j])
	{
		j = 0;
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'W', index))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			i += 1;
		ft_zero_index(index);
	}
	return (1);
}

int	ft_east_check(char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(map[i]) - 1;
	while (map[i] && map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'E', index))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			i += 1;
		if (map[i])
			j = ft_strlen(map[i]) - 1;
		ft_zero_index(index);
	}
	return (1);
}

int	ft_south_check(char **map, char **index)
{
	int		i;
	int		j;

	i = ft_arrlen(map) - 1;
	j = ft_strlen(map[i]) - 1;
	while (j >= 0)
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'S', index))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			j -= 1;
		// int k = 0;
		// while(index[k])
		// {
		// 	printf("index (%i): %s\n", k, index[k]);
		// 	k += 1;
		// }
		ft_zero_index(index);
	}
	return (1);
}

int	ft_north_check(char **map, char **index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'N', index))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			j += 1;
		// int k = 0;
		// while(index[k])
		// {
		// 	printf("index (%i): %s\n", k, index[k]);
		// 	k += 1;
		// }
		ft_zero_index(index);
	}
	return (1);
}

//north and west check has to be fixed, still error prone in case of carves
int	ft_wall_check(t_gamedata *config, int fd, char **index)
{
	if (!ft_south_check(config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("SOUTH"), config);
	}
	else if (!ft_north_check(config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("NORTH"), config);
	}
	else if (!ft_east_check(config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("EAST"), config);
	}
	else if (!ft_west_check(config->map, index))
	{
		ft_free(index);
		close(fd);
		ft_error_handling(10, ft_strdup("WEST"), config);
	}
	return (1);
}
