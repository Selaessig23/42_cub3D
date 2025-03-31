/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:33:36 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/31 14:57:09 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief vector addition in a 2D space
 * 
 * -> to move a ray forward step by step 
 * (ray_position = ray_position + ray_direction(==one ray))
 * -> for collision check
 * -> to move objects in a raycasted grip
 */
t_vector2	addvectors(t_vector2 vector1, t_vector2 vector2)
{
	t_vector2	newvector;

	newvector.x = vector1.x + vector2.x;
	newvector.y = vector1.y + vector2.y;
	return (newvector);
}
