/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:05:14 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/18 11:27:18 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub_s;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	sub_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (sub_s == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		sub_s[i] = s1[i];
		i++;
	}
	k = 0;
	while (s2[k] != '\0')
	{
		sub_s[i] = s2[k];
		k++;
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
