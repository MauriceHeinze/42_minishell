/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:06:09 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 14:02:00 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*new_s;
	char	new_c;

	i = ft_strlen(s);
	new_s = (char *)s;
	new_c = (char)c;
	while (i > 0)
	{
		if (new_s[i] == new_c)
			return (new_s + i);
		i--;
	}
	if (new_s[i] == new_c)
		return (new_s);
	return (NULL);
}
