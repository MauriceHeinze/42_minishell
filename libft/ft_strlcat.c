/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:05:48 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 11:27:21 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	i = d;
	if (size <= d)
		return (size + s);
	while (i + 1 < size && src[i - d])
	{
		dst[i] = src[i - d];
		i++;
	}
	dst[i] = '\0';
	return (s + d);
}
