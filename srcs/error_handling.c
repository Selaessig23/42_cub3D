/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:42:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/10 11:59:55 by mstracke         ###   ########.fr       */
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
		dprintf(2, "Please enter valid no of arguments for gaming fun (==1) \n");
	else if (err == 1)
		dprintf(2, "Wrong file format, please use extension \".cub\"\n");
	else if (err == 2)
		dprintf(2, "Unable to open the file: %s.\n", strerror(errno));
	else if (err == 3)
		dprintf(2, "Unable to read from the file: %s.\n", strerror(errno));
	exit (1);
}
