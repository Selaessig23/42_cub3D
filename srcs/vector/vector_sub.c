/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:36:53 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/27 16:41:49 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vector2 subtractvectors(t_vector2 vector1, t_vector2 vector2)
{
    t_vector2 newvector;

    newvector.x = vector1.x - vector2.x;
    newvector.y = vector1.y - vector2.y;
    return (newvector);
}
