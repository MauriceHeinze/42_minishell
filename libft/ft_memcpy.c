/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:36:03 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:32:00 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	if (n != 0)
	{
		n--;
		*((char *)(dst)) = *((char *)(src));
		while (n > 0)
		{
			*((char *)(dst + n)) = *((char *)(src + n));
			n--;
		}
	}
	return (dst);
}
