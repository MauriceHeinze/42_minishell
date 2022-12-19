/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:41:59 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/19 15:42:22 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_total_words(char **splitted)
{
	int		i;
	int		total_words;

	i = 0;
	total_words = 1;
	while (splitted[i] != NULL)
		total_words += count_words_operators(splitted[i++]);
	return (total_words);
}

char	**split_subline(char **splits)
{
	int		i;
	int		k;
	int		start;
	int		no_word;
	char	**words;

	init_to_zero(&i, &k, &start, &no_word);
	words = malloc(sizeof(char *) * get_total_words(splits));
	if (!words)
		return (NULL);
	while (splits[i] != NULL)
	{
		if (count_words_operators(splits[i]) == 1)
			words[no_word++] = ft_strdup(splits[i]);
		else
			acutal_split(splits, words, &i, &no_word);
		i++;
	}
	words[no_word] = NULL;
	return (words);
}