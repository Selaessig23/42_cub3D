/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:38:04 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/28 17:12:43 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vector2	dividevector(t_vector2 vector, double scalar)
{
	t_vector2	newvector;

	if (scalar == 0)
		return ((t_vector2){0, 0});
	newvector.x = vector.x / scalar;
	newvector.y = vector.y / scalar;
	return (newvector);
}
