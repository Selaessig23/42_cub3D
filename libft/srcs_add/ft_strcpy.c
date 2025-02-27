
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:46:23 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/27 10:46:29 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * DESCRIPTION:
 * The  strcpy()  function  copies the string pointed to by src, including
 * the terminating null byte ('\0'), to the buffer  pointed  to  by  dest.
 * The  strings  may  not overlap, and the destination string dest must be
 * large enough to receive the copy.  Beware  of  buffer  overruns!
 * 
 * @return returns a pointer to  the  destination string dest.
 */
char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

