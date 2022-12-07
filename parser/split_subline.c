/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:41:59 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/07 16:50:04 by mheinze          ###   ########.fr       */
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

static int	handle_quote(char **splitted, int *i, int *k, int *start)
{
	if (splitted[(*i)][(*k)] == '\"' || splitted[(*i)][(*k)] == '\'')
		(*k) = skip_quote(splitted[(*i)], (*k));
	while (!ft_strchr("|<>&", splitted[(*i)][(*k)]
		&& splitted[(*i)][(*k)] != '\0'))
		(*k)++;
	return ((*k));
}

char	*split_subline_helper(char **splitted, int *i, int *k, int *start)
{
	char	*tmp;

	if (op_found(splitted[(*i)][(*k)], splitted[(*i)][(*k) + 1]) == 2)
	{
		(*start) = (*k);
		(*k) += 2;
		return (ft_substr(splitted[(*i)], (*start), (*k) - (*start)));
	}
	else if ((splitted[(*i)][(*k)] == '<')
			|| (splitted[(*i)][(*k)] == '>')
			|| (splitted[(*i)][(*k)] == '|'))
	{
		(*start) = (*k);
		(*k)++;
		tmp = ft_substr(splitted[(*i)], (*start), (*k) - (*start));
		if (splitted[(*i)][(*k)] == ' ')
			(*k)++;
		return (tmp);
	}
	return (NULL);
}

char	*add_word(char **splitted, char **sub_splitted, int *no_word, int *i)
{
	int		k;
	int		start;
	char	*tmp;

	k = 0;
	tmp = NULL;
	while (splitted[(*i)][k] != '\0')
	{
		start = handle_quote(splitted, i, &k, &start);
		if (k > start)
			tmp = ft_substr(splitted[(*i)], start, k - start);
		if (op_found(splitted[(*i)][k], splitted[(*i)][k + 1]))
			tmp = split_subline_helper(splitted, i, &k, &start);
		else
			k++;
	}
	return (tmp);
}

char	**split_subline(char **splitted)
{
	int		i;
	int		k;
	int		start;
	int		no_word;
	char	**words;

	init_to_zero(&i, &k, &start, &no_word);
	words = malloc(sizeof(char *) * get_total_words(splitted));
	while (splitted[i] != NULL)
	{
		if (count_words_operators(splitted[i]) == 1)
			words[no_word++] = ft_strdup(splitted[i]);
		else
			words[no_word++] = add_word(splitted, words, &no_word, &i);
		i++;
	}
	words[no_word] = NULL;
	return (words);
}
