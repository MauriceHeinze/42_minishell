/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:41:59 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/08 18:36:26 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	double_operator_found(char a, char b)
{
	if (a == '<' && b == '<')
		return (1);
	else if (a == '>' && b == '>')
		return (1);
	else if (a == '&' && b == '&')
		return (1);
	else if (a == '|' && b == '|')
		return (1);
	return (0);
}

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

static void	acutal_split(char **splits, char **words, int *i, int *no_word)
{
	int	start;
	int	k;

	k = 0;
	while (splits[(*i)][k] != '\0')
	{
		start = k;
		if (splits[(*i)][k] == '\"' || splits[(*i)][k] == '\'')
			k = skip_quote(splits[(*i)], k);
		while (splits[(*i)][k] != '>' && splits[(*i)][k] != '<'
				&& splits[(*i)][k] != '|' && splits[(*i)][k] != '\0')
			k++;
		if (double_operator_found(splits[(*i)][k], splits[(*i)][k + 1]))
		{
			start = k;
			k += 2;
			words[(*no_word)++] = ft_substr(splits[(*i)], start, k - start);
			if (splits[(*i)][k] == ' ')
				k++;
		}
		else if (splits[(*i)][k] == '|' || splits[(*i)][k] == '>'
				|| splits[(*i)][k] == '<')
		{
			start = k;
			k++;
			words[(*no_word)++] = ft_substr(splits[(*i)], start, k - start);
			if (splits[(*i)][k] == ' ')
				k++;
		}
		else if (k > start)
			words[(*no_word)++] = ft_substr(splits[(*i)], start, k - start);
		else
			k++;
	}
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
