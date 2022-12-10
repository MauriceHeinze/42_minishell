/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:06:09 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 14:57:17 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*new_s;
	char	new_c;
	size_t	i;

	new_s = (char *)s;
	new_c = (char)c;
	i = 0;
	while (new_s[i] != '\0')
	{
		if (new_s[i] == new_c)
			return (new_s + i);
		i++;
	}
	if (new_s[i] == new_c)
		return (new_s + i);
	return (NULL);
}
