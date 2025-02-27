/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:37:05 by pvasilan          #+#    #+#             */
/*   Updated: 2025/02/27 16:59:34 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int setInitialPosition(t_gamedata *config);
int setInitialDirection(t_gamedata *config);
int initPlayer(t_gamedata *config);

//Raycasting functions
void            castRays(t_gamedata *config);
void            castSingleRay(t_gamedata *config, int rayIndex);
t_vector2       calculateRayDirection(t_gamedata *config, int rayIndex);
bool            checkRayCollision(t_gamedata *config, int rayIndex);
int             calculateWallHitDistance(t_gamedata *config, int rayIndex);
int             calculateWallHeight(t_gamedata *config, int rayIndex);
t_vector2       calculateWallTextureCoordinates(t_gamedata *config, int rayIndex);
mlx_texture_t*  selectTexturebyDirection(t_gamedata *config, int direction);



//this function takes the color of texture at position x,y and returns it for drawing
t_color getTexelColor(mlx_texture_t *texture, int x, int y);

