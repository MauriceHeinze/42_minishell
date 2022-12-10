/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:41:26 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/24 14:48:00 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wrdcnt(char const *s, char c)
{
	size_t	i;
	int		nparts;

	i = 0;
	nparts = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c))
			i++;
		if (s[i] != c && s[i] != '\0')
			nparts++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (nparts);
}

static char	**ft_split_words(char	**words, char const *s, char c)
{
	size_t	i;
	size_t	k;
	int		nparts;

	i = 0;
	k = 0;
	nparts = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c))
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			k++;
		}
		if (k > 0)
		{
			words[nparts] = ft_substr(s, i - k, k);
			nparts++;
			k = 0;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = ft_calloc(ft_wrdcnt(s, c) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	return (ft_split_words(words, s, c));
}
