/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:42:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/05 17:36:25 by mstracke         ###   ########.fr       */
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
		dprintf(2, "please enter valid no of arguments for gaming fun (==1) \n");
	else if (err == 1)
		dprintf(2, "wrong file format, please use extension \".cub\"\n");
	exit (1);
}
