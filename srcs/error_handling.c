/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:42:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/10 17:29:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief function to organise error handling
 * print error messages and free allocated memory
 * 
 * @param err own error-code
 */
void	ft_error_handling(int err)
{
	if (err == 0)
	{
		ft_dprintf(2, "Please enter valid no of arguments for "
			"gaming fun (==1) \n");
	}
	else if (err == 1)
		ft_dprintf(2, "Wrong file format, please use extension \".cub\"\n");
	else if (err == 2)
		ft_dprintf(2, "Unable to open the file: %s.\n", strerror(errno));
	else if (err == 3)
		ft_dprintf(2, "Unable to read from the file: %s.\n", strerror(errno));
	else if (err == 9)
		ft_dprintf(2, "Malloc problems.\n");
	exit (1);
}
