/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:23 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/27 16:41:38 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vector2 rotatevector(t_vector2 vector, double angle)
{
    t_vector2 newvector;

    newvector.x = vector.x * cos(angle) - vector.y * sin(angle);
    newvector.y = vector.x * sin(angle) + vector.y * cos(angle);
    return (newvector);
}
