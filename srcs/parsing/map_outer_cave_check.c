/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_outer_cave_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:15:38 by mstracke          #+#    #+#             */
/*   Updated: 2025/04/10 19:48:02 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * DESCRIPTION:
 * file to check if the outer cave of tha map (consisting of spaces)
 * is surrounded by walls
 */

/**
 * @brief checks one field in the map if it is a wall (1), floor (0)
 * or an empty space
 *
 * If it is a space it overwrites the space with a 'C', which means
 * that this field of the grid was already checked, and returns 0.
 *
 * If it is a wall or index is < 0 (which means the edge of
 * the grid was reached) it returns 1.
 *
 * If it is a floor (0), here: 'else'-condition,  it returns -1.
 */
int	ft_check_field(char **map, int startarr, int startstr)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if ((size_t)startarr >= ft_arrlen(map)
		|| (size_t)startstr >= ft_strlen(map[startarr]))
		return (1);
	if (map[startarr][startstr] == 'C')
		return (0);
	if (map[startarr][startstr] == ' ')
	{
		map[startarr][startstr] = 'C';
		return (0);
	}
	else if (map[startarr][startstr] == '1')
	{
		return (1);
	}
	else
		return (-1);
}

/**
 * @brief function to check the west-east passage,
 * important if coming from north or south
 *
 * if one of the fields is checked to be a floor,
 * it returns 0.
 *
 * if one of the fields is out of the edge of the grid,
 * a wall, or was already checked (marked with 'C')
 * it returns 1.
 *
 * if one of the field is checked to be a space,
 * it re-calls the function ft_check_cave to check
 * if this cave-extension is wall-proteced as well
 * (recursive part)
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
	if ((size_t)startarr >= ft_arrlen(map)
		|| (size_t)startstr >= ft_strlen(map[startarr])
		|| map[startarr][startstr] == 'C')
		return (1);
	if (ft_check_field(map, startarr, startstr - 1) < 0
		|| ft_check_field(map, startarr, startstr + 1) < 0
		|| ft_check_field(map, startarr, startstr) < 0)
		return (0);
	if (ft_check_field(map, startarr, startstr - 1) == 0)
		if (!ft_check_cave(map, startarr, startstr - 1, 'E'))
			return (0);
	if (ft_check_field(map, startarr, startstr + 1) == 0)
		if (!ft_check_cave(map, startarr, startstr + 1, 'W'))
			return (0);
	if (ft_check_field(map, startarr, startstr) == 0)
		if (!ft_check_cave(map, startarr, startstr, prev_direction))
			return (0);
	return (1);
}

/**
 * @brief function to check the north-south passage,
 * important if coming from east or west
 *
 * if one of the fields is checked to be a floor,
 * it returns 0.
 *
 * if one of the fields is out of the edge of the grid,
 * a wall, or was already checked (marked with 'C')
 * it returns 1.
 *
 * if one of the field is checked to be a space,
 * it re-calls the function ft_check_cave to check
 * if this cave-extension is wall-proteced as well
 * (recursive part)
 *
 * check: fields with * (+ means already checked)
 *   +  +  + *
 *   +  +  > *
 *   +  +  + *
 */
int	ft_check_ns_passage(char **map, int startarr, int startstr,
	char prev_direction)
{
	if (startarr < 0 || startstr < 0)
		return (1);
	if ((size_t)startarr >= ft_arrlen(map)
		|| (size_t)startstr >= ft_strlen(map[startarr])
		|| map[startarr][startstr] == 'C')
		return (1);
	if (ft_check_field(map, startarr - 1, startstr) < 0
		|| ft_check_field(map, startarr + 1, startstr) < 0
		|| ft_check_field(map, startarr, startstr) < 0)
		return (0);
	if (ft_check_field(map, startarr - 1, startstr) == 0)
		if (!ft_check_cave(map, startarr - 1, startstr, 'S'))
			return (0);
	if (ft_check_field(map, startarr + 1, startstr) == 0)
		if (!ft_check_cave(map, startarr + 1, startstr, 'N'))
			return (0);
	if (ft_check_field(map, startarr, startstr) == 0)
		if (!ft_check_cave(map, startarr, startstr, prev_direction))
			return (0);
	return (1);
}

/**
 * @brief cave check function (recursive)
 * 2nd part of ft_check_cave
 * check if the cave was registered coming from an
 * eastern or western direction
 * 1st part see below
 *
 * @return 0 in case there was a floor instead of expected wall,
 * 1 in case of surrounded by walls
 *
 */
static int	ft_check_cave_ii(char **map, int startarr, int startstr,
	char prev_direction)
{
	if (prev_direction == 'E')
	{
		if (ft_check_ns_passage(map, startarr, startstr - 1, prev_direction))
			return (1);
		else
			return (0);
	}
	else
	{
		if (ft_check_ns_passage(map, startarr, startstr + 1, prev_direction))
			return (1);
		else
			return (0);
	}
}

/**
 * @brief function that organises the cave-check by
 * sending it to a field checker depending on which direction
 * the cave (space) was found. If there is another space found in
 * ft_check_we_passage or ft_check_ns_passage this function will be
 * called recursively
 *
 * 1st part: check if the cave was registered coming from an
 * souther or northern direction
 * 2nd part: see above
 *
 * * @return 0 in case there was a floor instead of expected wall,
 * 1 in case of surrounded by walls
 *
 * maybe delete this function (& ft_check_cave_ii)
 * and call the corresponding
 * function directly in direction check or passage check
 */
int	ft_check_cave(char **map, int startarr, int startstr,
		char prev_direction)
{
	if (prev_direction == 'N')
	{
		if (ft_check_we_passage(map, startarr + 1, startstr, prev_direction))
			return (1);
		else
			return (0);
	}
	else if (prev_direction == 'S')
	{
		if (ft_check_we_passage(map, startarr - 1, startstr, prev_direction))
			return (1);
		else
			return (0);
	}
	else
		return (ft_check_cave_ii(map, startarr, startstr, prev_direction));
}
