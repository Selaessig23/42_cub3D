#include "cub3d.h"

int ft_check_field(char **map,  int startarr, int startstr)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if (!map[startarr] || !map[startarr][startstr])
		return (1);
	if (map[startarr][startstr] == ' ')
		return (0);
	else if (map[startarr][startstr] == '1')
		return (1);
	else
		return (-1);
}

int	ft_check_we_passage(char **map, int startarr, int startstr, 
		char prev_direction)
{
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
	// printf("test yes\n");
	return (1);
}

int	ft_check_ns_passage(char **map, int startarr, int startstr, 
	char prev_direction)
{
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
	return (1);
}

int	ft_check_carve(char **map, int startarr, int startstr, 
	char prev_direction)
{
	printf("test arr: %i, str: %i\n", startarr, startstr);
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
