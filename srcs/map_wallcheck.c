#include "cub3d.h"

/**
 * DESCRIPTION: 
 * file to check if the map is closed/surrounded by walls, 
 * if not the program must returns an errormessage and exits.
 * 
 * check what happens if map starts with 0
 */

int	ft_south_check(char **map);
int	ft_west_check(char **map);
int	ft_east_check(char **map);
int	ft_north_check(char **map);

int	ft_west_check(char **map)
{
	int		i;
	int		j;
	//int		k;

	i = 0;
	j = 0;
	//k = 0;
	while (map[i] && map[i][j])
	{
		j = 0;
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'W'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			i += 1;
	}
	return (1);
}

int	ft_east_check(char **map)
{
	int		i;
	int		j;
	//int		k;

	i = 0;
	j = ft_strlen(map[i]) - 1;
	//k = 0;
	while (map[i] && map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'E'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			i += 1;
		if (map[i])
			j = ft_strlen(map[i]) - 1;
	}
	return (1);
}
/*
int	ft_spacewall_check(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	else 
		return (0);
}

int	ft_closed_by_wall(char **map, int startarr, int startstr)
{
	printf("test2: arr: %i, str: %i\n", startarr, startstr);
	if (startstr - 1 >= 0 
		&& !ft_spacewall_check(map[startarr][startstr - 1]))
	{
		printf("A\n");
		return (0);
	}
	else if (!ft_spacewall_check(map[startarr][startstr + 1]))
	{
		printf("B\n");
		return (0);
	}
	else if (startarr - 1 >= 0 && map[startarr - 1][startstr]
		&& !ft_spacewall_check(map[startarr - 1][startstr]))
	{
		printf("C: %c\n", map[startarr - 1][startstr]);
		return (0);
	}
	else if (startarr -1 >= 0 && startstr >= 1 
		&& !ft_spacewall_check(map[startarr - 1][startstr - 1]))
	{
		printf("D\n");
		return (0);
	}
	else if (startarr >= 0 && map[startarr - 1][startstr + 1]
		&& !ft_spacewall_check(map[startarr - 1][startstr + 1]))
	{
		printf("E\n");
		return (0);
	}
	else if (map[startarr + 1] && map[startarr + 1][startstr]
		&& !ft_spacewall_check(map[startarr + 1][startstr]))
	{
		printf("F\n");
		return (0);
	}
	else if (map[startarr + 1] && startstr >= 0
		&& !ft_spacewall_check(map[startarr + 1][startstr - 1]))
	{
		printf("G\n");
		return (0);
	}
	else if (map[startarr + 1] && map[startarr + 1][startstr + 1] 
		&& !ft_spacewall_check(map[startarr + 1][startstr + 1]))
	{
		printf("H\n");
		return (0);
	}
	printf("why?\n");
	return (1);
}

int	ft_check_surrounding(char **map, int startarr, int startstr, 
	char prev_direction)
{
	printf("test: arr: %i, str: %i\n", startarr, startstr);
	if (startstr - 1 >= 0 && map[startarr][startstr - 1] == ' ' && prev_direction != 'W')
	{
		printf("test A: 0 -1\n");
		if (!ft_check_surrounding(map, startarr, startstr - 1, 'E'))
			return (0);
	}
	if (map[startarr][startstr + 1] && map[startarr][startstr + 1] == ' ' && prev_direction != 'E')
	{
		printf("test A: 0 +1\n");
		if (!ft_check_surrounding(map, startarr, startstr + 1, 'W'))
			return (0);
	}
	if (startarr >= 0 && map[startarr - 1][startstr]
		&& map[startarr - 1][startstr] == ' ' && prev_direction != 'N')
	{
		printf("test A: -1 0\n");
		if (!ft_check_surrounding(map, startarr - 1, startstr, 'S'))
			return (0);
	}
	if (startarr >= 0 && startstr - 1 >= 0
		&& map[startarr - 1][startstr - 1] == ' ' && prev_direction != 'N' && prev_direction != 'E')
	{
		printf("test A: -1 -1\n");
		if (!ft_check_surrounding(map, startarr - 1, startstr - 1, 0))
			return (0);
	}
	if (startarr >= 0 && map[startarr - 1][startstr + 1]
		&& map[startarr - 1][startstr + 1] == ' ' && prev_direction != 'N')
	{
		printf("test A: -1 +1\n");
		if (!ft_check_surrounding(map, startarr - 1, startstr + 1, 0))
			return (0);
	}
	if (map[startarr + 1] && map[startarr + 1][startstr]
		&& map[startarr + 1][startstr] == ' ' && prev_direction != 'S')
	{
		printf("test A: +1 0\n");
		if (!ft_check_surrounding(map, startarr + 1, startstr, 'N'))
			return (0);
	}
	if (map[startarr + 1] && startstr - 1 >= 0
		&& map[startarr + 1][startstr - 1] == ' ' && prev_direction != 'S')
	{
		printf("test A: +1 -1\n");
		if (!ft_check_surrounding(map, startarr + 1, startstr - 1, 0))
			return (0);
	}
	if (map[startarr + 1] && map[startarr + 1][startstr + 1] 
		&& map[startarr + 1][startstr + 1] == ' ' && prev_direction != 'S')
	{
		printf("test A: +1 +1\n");
		if (!ft_check_surrounding(map, startarr + 1, startstr + 1, 0))
			return (0);
	}
	// printf("test\n");
	if (!ft_closed_by_wall(map, startarr, startstr))
	{
		printf("hae\n");
		return (0);
	}
	return (1);
}
*/

int	ft_south_check(char **map)
{
	int		i;
	int		j;
	int		k;

	i = ft_arrlen(map) - 1;
	j = ft_strlen(map[i]) - 1;
	k = 0;
	while (j >= 0)
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'S'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			j -= 1;
	}
	return (1);
}

int	ft_north_check(char **map)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == ' ' && !ft_check_carve(map, i, j, 'N'))
			return (0);
		else if (map[i][j] == '0')
			return (0);
		else
			j += 1;
	}
	return (1);
}

//north and west check has to be fixed, still error prone in case of carves
int	ft_wall_check(t_gamedata *config, int fd)
{
	int		i;

	i = 0;
	if (!ft_south_check(config->map))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("SOUTH"), config);
	}
	// else if (!ft_north_check(config->map))
	// {
	// 	close(fd);
	// 	ft_error_handling(10, ft_strdup("NORTH"), config);
	// }
	else if (!ft_east_check(config->map))
	{
		close(fd);
		ft_error_handling(10, ft_strdup("EAST"), config);
	}
	// else if (!ft_west_check(config->map))
	// {
	// 	close(fd);
	// 	ft_error_handling(10, ft_strdup("WEST"), config);
	// }
	return (1);
}
