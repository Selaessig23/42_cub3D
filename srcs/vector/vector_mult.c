/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:53 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/15 16:50:39 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vector2	multiplyvector(t_vector2 vector, double scalar)
{
	t_vector2	newvector;

	newvector.x = vector.x * scalar;
	newvector.y = vector.y * scalar;
	return (newvector);
}
