/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:38:04 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/27 16:40:48 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vector2 dividevector(t_vector2 vector, double scalar)
{
    t_vector2 newvector;

    newvector.x = vector.x / scalar;
    newvector.y = vector.y / scalar;
    return (newvector);
}
