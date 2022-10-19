/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_backslash.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:08:00 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/19 17:13:09 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_edgecase(char const *s, unsigned int start, size_t len)
{
	if (len > (ft_strlen(s) - start))
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr_backslash(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	len = ft_edgecase(s, start, len);
	if (start >= ft_strlen(s))
	{
		sub_s = malloc(sizeof(char) * 1);
		if (!sub_s)
			return (NULL);
		sub_s[0] = '\0';
		return (sub_s);
	}
	sub_s = malloc(sizeof(char) * len + 1);
	if (sub_s == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (i < len)
	{
		if (s[start + i] == '\\')
			i++;
		sub_s[k++] = s[start + i++];
	}
	sub_s[len] = '\0';
	return (sub_s);
}

// int	main(void)
// {
// 	ft_substr("tripouille", 1, 1);
// 	return (0);
// }
