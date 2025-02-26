#include "cub3d.h"

/**
 * @brief checks one field in the map if it is a wall (1 or ' ')
 * or an empty space (floor)
 */
int ft_check_field(char **map,  int startarr, int startstr)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if ((size_t)startarr >= ft_arrlen(map) 
		|| (size_t)startstr >= ft_strlen(map[startarr]))
	// if (!map[startarr] || !map[startarr][startstr])
		return (1);
	// index[startarr][startstr] = map[startarr][startstr];
	// if (map[startarr][startstr] == ' ')
	// {
	// 	index[startarr][startstr] = map[startarr][startstr];
	// 	return (0);
	// }
	if (map[startarr][startstr] == 'C')
		return (0);
	if (map[startarr][startstr] == ' ')
	{
		map[startarr][startstr] = 'C';
		return (0);
	}
	// else if (map[startarr][startstr] == '1')
	// {
	// 	index[startarr][startstr] = map[startarr][startstr];
	// 	return (1);
	// }
	else if (map[startarr][startstr] == '1')
	{
		// map[startarr][startstr] = 'C';
		return (1);
	}
	else
		return (-1);
}

/**
 * @brief function to check the west-east passage,
 * important if coming from north or south
 * 
 * check: fields with * (+ means already checked)
 *   *  *  *
 *   +  ^  +
 *   +  +  +
 */
int	ft_check_we_passage(char **map, int startarr, int startstr, 
		char prev_direction)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	// if (!map[startarr] || !map[startarr][startstr]
	if ((size_t)startarr >= ft_arrlen(map) 
		|| (size_t)startstr >= ft_strlen(map[startarr])
		|| map[startarr][startstr] == 'C')
		return (1);
	if (ft_check_field(map, startarr, startstr - 1) < 0
		|| ft_check_field(map, startarr, startstr + 1) < 0
		|| ft_check_field(map, startarr, startstr) < 0)
		return (0);
	if (ft_check_field(map, startarr, startstr - 1) == 0)
		if (!ft_check_carve(map, startarr, startstr - 1, 'E'))
			return (0);
	if (ft_check_field(map, startarr, startstr + 1) == 0)
		if (!ft_check_carve(map, startarr, startstr + 1, 'W'))
			return (0);
	if (ft_check_field(map, startarr, startstr) == 0)
		if (!ft_check_carve(map, startarr, startstr, prev_direction))
			return (0);
	// printf("test yes: map-1 = %c, map0 = %c, map+1 = %c\n", map[startarr][startstr - 1], map[startarr][startstr], map[startarr][startstr + 1]);
	return (1);
}

/**
 * @brief function to check the north-south passage,
 * important if coming from east or west
 * 
 * check: fields with * (+ means already checked)
 *   +  +   *
 *   +  + ->*
 *   +  +   *
 */
int	ft_check_ns_passage(char **map, int startarr, int startstr, 
	char prev_direction)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	// if (!map[startarr] || !map[startarr][startstr]
	if ((size_t)startarr >= ft_arrlen(map) 
		|| (size_t)startstr >= ft_strlen(map[startarr])
		|| map[startarr][startstr] == 'C')
		return (1);
	if (ft_check_field(map, startarr - 1, startstr) < 0
		|| ft_check_field(map, startarr + 1, startstr) < 0
		|| ft_check_field(map, startarr, startstr) < 0)
		return (0);
	if (ft_check_field(map, startarr - 1, startstr) == 0)
		if (!ft_check_carve(map, startarr - 1, startstr, 'S'))
			return (0);
	if (ft_check_field(map, startarr + 1, startstr) == 0)
		if (!ft_check_carve(map, startarr + 1, startstr, 'N'))
			return (0);
	if (ft_check_field(map, startarr, startstr) == 0)
		if (!ft_check_carve(map, startarr, startstr, prev_direction))
			return (0);
	// printf("test 2 yes\n");
	return (1);
}

//maybe delete this function and call the corresponding 
//function directly in direction check or 
//passage check
int	ft_check_carve(char **map, int startarr, int startstr, 
	char prev_direction)
{
	// printf("test arr: %i, str: %i\n", startarr, startstr);
	if (prev_direction == 'N')
	{
		// printf("yes north\n");
		if (ft_check_we_passage(map, startarr + 1, startstr, prev_direction))
			return (1);
		else
			return (0);
	}
	else if (prev_direction == 'S')
	{
		// printf("yes south\n");
		if (ft_check_we_passage(map, startarr - 1, startstr, prev_direction))
			return (1);
		else
			return (0);
	}
	else if (prev_direction == 'E')
	{
		if (ft_check_ns_passage(map, startarr, startstr - 1, prev_direction))
			return (1);
		else
			return (0);
	}
	// else if (prev_direction == 'W')
	else
	{
		if (ft_check_ns_passage(map, startarr, startstr + 1, prev_direction))
			return (1);
		else
			return (0);
	}
}
