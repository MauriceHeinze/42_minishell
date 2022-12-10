/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:25:26 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 11:26:41 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	i = 0;
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	if (!ptr_dest && !ptr_src)
		return (NULL);
	if (ptr_dest > ptr_src)
	{
		while (++i <= n)
			ptr_dest[n - i] = ptr_src[n - i];
	}
	else
	{
		while (n > 0)
		{
			ptr_dest[i] = ptr_src[i];
			n--;
			i++;
		}
	}
	return (dest);
}
