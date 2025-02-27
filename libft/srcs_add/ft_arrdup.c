
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:06:17 by mstracke          #+#    #+#             */
/*   Updated: 2025/02/27 11:06:19 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * DESCRIPTION:
 * dupliactes an array of strings including terminating NULL
 * 
 * @return a pointer to the new array dest
 */
char	**ft_arrdup(char **src)
{
	char	**dest;
	int		i;

	i = ft_arrlen(src);
	dest = (char **)malloc((i + 1) * sizeof(char *));
	if (!dest)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i += 1;
	}
	dest[i] = NULL;
	return (dest);
}
