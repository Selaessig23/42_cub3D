/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:10:37 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/12 15:22:35 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../libft/include/libft_bonus.h"
# include <unistd.h>
# include <stdio.h>
# include <math.h>
//check https://harm-smits.github.io/42docs/libs/minilibx/
//getting_started.html#installation
//for good documentation of the minilibx-library
# include "../MLX42/include/MLX42/MLX42.h"
//to communicate with X server / X Window System (X11)
# include <X11/X.h>
//well documented at https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h
# include <X11/keysym.h>
//to define which set is used in render.c
# include <stdbool.h>
//to provide a standardized way to report and interpret error conditions
# include <errno.h>

typedef struct s_cub3d
{
	mlx_t* mlx;
} t_cub3d;

//command_line_input_check.c
int			ft_access_check(char *inputfile);
int			ft_extension_check(char *input);
//error_handling.c
void		ft_error_handling(int err);

#endif
