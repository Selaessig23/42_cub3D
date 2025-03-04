/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:42:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/03/04 12:32:57 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error_parsing_1(int err, char *addinfo)
{
	if (err == 0)
	{
		ft_dprintf(2, "Please enter valid no of arguments for "
			"gaming fun (==1) \n");
	}
	else if (err == 1)
		ft_dprintf(2, "Wrong file format, please use extension \".cub\"\n");
	else if (err == 2)
		ft_dprintf(2, "Unable to open the file: \'%s\'. %s.\n", 
			addinfo, strerror(errno));
	else if (err == 3)
		ft_dprintf(2, "Unable to read from the file: \'%s\'. "
			"%s.\n", addinfo, strerror(errno));
	else if (err == 4)
		ft_dprintf(2, "Content of identifier %s is missing.\n", addinfo);
	else if (err == 5)
		ft_dprintf(2, "Required infos in input file "
			"are missing: %s!\n", addinfo);
	else if (err == 6)
		ft_dprintf(2, "Color values are wrong\n");
	else if (err == 7)
		ft_dprintf(2, "Map input is wrong. Wrong character(s).\n");
	else if (err == 8)
		ft_dprintf(2, "There are more than one idenitifer for %s.\n", addinfo);
}

void	ft_error_parsing_2(int err, char *addinfo)
{
	if (err == 10)
		ft_dprintf(2, "The map is not surrounded by walls in %s.\n", addinfo);
	else if (err == 11)
		ft_dprintf(2, "How will you have fun without "
			"any player in game, idiot? Check your map, it is invalid!\n");
	else if (err == 12)
		ft_dprintf(2, "How will you play with several players "
			"at the same time, idiot? Check your map, it is invalid!\n");
}

/**
 * @brief function to organise error handling
 * print error messages and free allocated memory
 * 
 * @param err own error-code
 */
void	ft_error_handling(int err, char *addinfo, t_gamedata *config)
{
	if (err < 0)
		ft_error_parsing_1(err, addinfo);
	else if (err == 9)
		ft_dprintf(2, "Malloc problems.\n");
	else if (err > 9 && err < 20)
		ft_error_parsing_2(err, addinfo);
	if (config)
		ft_free_config(config);
	if (addinfo)
		free(addinfo);
	exit (1);
}
