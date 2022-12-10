/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:07:48 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/29 16:49:20 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		str_len;
	char		*trimmed;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	str_len = ft_strlen(s1);
	while (str_len && ft_strchr(set, s1[str_len]))
		str_len--;
	trimmed = ft_substr((char *)s1, 0, str_len + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
