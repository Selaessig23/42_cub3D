/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:22:43 by mstracke          #+#    #+#             */
/*   Updated: 2024/01/17 13:53:16 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"
# include <stdarg.h>

//printf functions
int		ft_dprintf(int fd, const char *format, ...);
int		ft_dprintui(int fd, va_list args);
int		ft_dprintint(int fd, va_list args);
int		ft_dprinthexa(int fd, va_list args, char *c);
int		ft_dprintpointer(int fd, va_list args, char *c);
int		ft_dprintstring(int fd, va_list args);
int		ft_dprintchar(int fd, va_list args);

#endif
