/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:04:23 by mheinze           #+#    #+#             */
/*   Updated: 2022/06/15 16:52:01 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (size > 0 && (18446744073709551615UL / size) < count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return ((void *)ptr);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*x;

// 	x = malloc(count * size);
// 	if (x == NULL)
// 		return (NULL);
// 	ft_bzero(x, count * size);
// 	return (x);
// }
