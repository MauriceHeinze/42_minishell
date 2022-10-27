/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:12:41 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:01:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	l;

	l = 0;
	if (n == 0)
		return (0);
	while (*(s1 + l) != 0 && *(s2 + l) != 0 && l < n - 1)
	{
		if (*(s1 + l) != *(s2 + l))
		{
			if ((unsigned char)*(s1 + l) > (unsigned char)*(s2 + l))
				return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
			if ((unsigned char)*(s1 + l) < (unsigned char)*(s2 + l))
				return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
		}
		l++;
	}
	if (*(s1 + l) != *(s2 + l))
	{
		if ((unsigned char)*(s1 + l) > (unsigned char)*(s2 + l))
			return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
		if ((unsigned char)*(s1 + l) < (unsigned char)*(s2 + l))
			return ((unsigned char)*(s1 + l) - (unsigned char)*(s2 + l));
	}
	return (0);
}
