/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:08:39 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/26 14:48:05 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function that imitates strncpy - copy a string
 * The strcpy() function copies the string pointed to by src, 
 * including the terminating null byte ('\0'), to the buffer 
 * pointed to by dest. The strings may not overlap, and the destination
 * string dest must be large enough to receive the copy.
 * 
 * @return a pointer to the destination string dest
 * 
 */
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
