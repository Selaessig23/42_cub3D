/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:42:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/19 10:00:54 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief function to organise error handling
 * print error messages and free allocated memory
 * 
 * @param err own error-code
 */
void	ft_error_handling(int err, char *addinfo, t_gamedata *config)
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
		ft_dprintf(2, "Path of texture %s is missing\n", addinfo);
	else if (err == 5)
		ft_dprintf(2, "Required infos in input file "
			"are missing: %s!\n", addinfo);
	else if (err == 6)
		ft_dprintf(2, "Color values are wrong\n");
	else if (err == 7)
		ft_dprintf(2, "Map input is wrong. Wrong character(s).\n");
	else if (err == 8)
		ft_dprintf(2, "There are more than one idenitifer for %s.\n", addinfo);
	else if (err == 9)
		ft_dprintf(2, "Malloc problems.\n");
	else if (err == 10)
		ft_dprintf(2, "The map is not surrounded by walls.\n");
	if (config)
		ft_free_config(config);
	if (addinfo)
		free(addinfo);
	exit (1);
}
