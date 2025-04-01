/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:23 by pvasilan          #+#    #+#             */
/*   Updated: 2025/04/01 10:23:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief rotates a 2D vector by an angle,
 * especially to rotate the player's direction vector
 * in case of key-input
 * 
 * It applies the 2D rotation matrix to the vector:
 * [x′/y′] = [cos⁡(θ) − sin⁡(θ) / sin⁡(θ) - cos⁡(θ)] * [x / y]
 * which expands to 
 * x′ = x⋅cos(θ) − y * sin(θ)
 * y′ = x⋅sin⁡(θ) + y * cos⁡(θ)
 */
t_vector2	rotatevector(t_vector2 vector, double angle)
{
	t_vector2	newvector;

	newvector.x = vector.x * cos(angle) - vector.y * sin(angle);
	newvector.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (newvector);
}
