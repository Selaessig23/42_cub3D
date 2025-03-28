/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:36 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/28 17:11:00 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief A normalized vector keeps the same direction but 
 * scales its length to exactly 1. This is useful when you only 
 * care about where a vector points, not how long it is.
 */
t_vector2	normalizevector(t_vector2 vector)
{
	double	length;

	length = vectorln(vector);
	if (length == 0)
		return ((t_vector2){0, 0});
	return (dividevector(vector, length));
}
