/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:50:54 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:01:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	checklength(char *start)
{
	int	c;

	c = 0;
	while (*(start + c) != 0)
		c++;
	return (c);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	lsrc;
	unsigned int	i;

	i = 0;
	lsrc = checklength((char *)src);
	if (lsrc >= dstsize && dstsize > 0)
	{
		while (i < dstsize -1)
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = 0;
	}
	else if (dstsize > 0)
	{
		while (i < lsrc)
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = 0;
	}
	return (lsrc);
}
