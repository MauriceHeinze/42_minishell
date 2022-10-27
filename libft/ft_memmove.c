/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:45:53 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:01:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (len != 0 || dst != src)
	{
		if (dst > src)
		{
			while (len > 0)
			{
				*((char *)(dst + len -1)) = *((char *)(src + len -1));
				len--;
			}
		}
		else
		{
			while (i < len)
			{
				*((char *)(dst + i)) = *((char *)(src + i));
				i++;
			}
		}
	}
	return (dst);
}
