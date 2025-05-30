/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ln.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:58 by pvasilan          #+#    #+#             */
/*   Updated: 2025/03/27 15:31:33 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	vectorln(t_vector2 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y));
}
