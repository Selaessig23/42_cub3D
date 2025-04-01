/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:53 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/01 10:26:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief scalar multiplication: 
 * It scales the vector’s magnitude while maintaining its direction.
 * 
 * 
 */
t_vector2	multiplyvector(t_vector2 vector, double scalar)
{
	t_vector2	newvector;

	newvector.x = vector.x * scalar;
	newvector.y = vector.y * scalar;
	return (newvector);
}
