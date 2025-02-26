#include "cub3d.h"

/**
 * @brief checks one field in the map if it is a wall (1 or ' ')
 * or an empty space (floor)
 */
int ft_check_field(char **map,  int startarr, int startstr, char **index)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if (!map[startarr] || !map[startarr][startstr])
		return (1);
	// index[startarr][startstr] = map[startarr][startstr];
	if (map[startarr][startstr] == ' ')
	{
		index[startarr][startstr] = map[startarr][startstr];
		return (0);
	}
	else if (map[startarr][startstr] == '1')
	{
		index[startarr][startstr] = map[startarr][startstr];
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
		char prev_direction, char **index)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if (!map[startarr] || !map[startarr][startstr]
		|| index[startarr][startstr] != '-')
		return (1);
	if (ft_check_field(map, startarr, startstr - 1, index) < 0
		|| ft_check_field(map, startarr, startstr + 1, index) < 0
		|| ft_check_field(map, startarr, startstr, index) < 0)
		return (0);
	if (ft_check_field(map, startarr, startstr - 1, index) == 0)
		if (!ft_check_carve(map, startarr, startstr - 1, 'E', index))
			return (0);
	if (ft_check_field(map, startarr, startstr + 1, index) == 0)
		if (!ft_check_carve(map, startarr, startstr + 1, 'W', index))
			return (0);
	if (ft_check_field(map, startarr, startstr, index) == 0)
		if (!ft_check_carve(map, startarr, startstr, prev_direction, index))
			return (0);
	printf("test yes\n");
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
	char prev_direction, char **index)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if (!map[startarr] || !map[startarr][startstr]
		|| index[startarr][startstr] != '-')
		return (1);
	if (ft_check_field(map, startarr - 1, startstr, index) < 0
		|| ft_check_field(map, startarr + 1, startstr, index) < 0
		|| ft_check_field(map, startarr, startstr, index) < 0)
		return (0);
	if (ft_check_field(map, startarr - 1, startstr, index) == 0)
		if (!ft_check_carve(map, startarr - 1, startstr, 'S', index))
			return (0);
	if (ft_check_field(map, startarr + 1, startstr, index) == 0)
		if (!ft_check_carve(map, startarr + 1, startstr, 'N', index))
			return (0);
	if (ft_check_field(map, startarr, startstr, index) == 0)
		if (!ft_check_carve(map, startarr, startstr, prev_direction, index))
			return (0);
	printf("test 2 yes\n");
	return (1);
}

//maybe delete this function and call the corresponding function directly in direction check or 
//passage check
int	ft_check_carve(char **map, int startarr, int startstr, 
	char prev_direction, char **index)
{
	printf("test arr: %i, str: %i\n", startarr, startstr);
	if (prev_direction == 'N')
	{
		// printf("yes north\n");
		if (ft_check_we_passage(map, startarr + 1, startstr, prev_direction, index))
			return (1);
		else
			return (0);
	}
	else if (prev_direction == 'S')
	{
		// printf("yes south\n");
		if (ft_check_we_passage(map, startarr - 1, startstr, prev_direction, index))
			return (1);
		else
			return (0);
	}
	else if (prev_direction == 'E')
	{
		if (ft_check_ns_passage(map, startarr, startstr - 1, prev_direction, index))
			return (1);
		else
			return (0);
	}
	// else if (prev_direction == 'W')
	else
	{
		if (ft_check_ns_passage(map, startarr, startstr + 1, prev_direction, index))
			return (1);
		else
			return (0);
	}
}
