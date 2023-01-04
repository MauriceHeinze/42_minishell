/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subline_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:41:59 by mheinze           #+#    #+#             */
/*   Updated: 2023/01/04 16:31:36 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	double_operator_found(char a, char b)
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

static int	skip(char **splits, int *i, int *k)
{
	int	old_k;

	old_k = (*k);
	if (splits[(*i)][(*k)] == '\"' || splits[(*i)][(*k)] == '\'')
			(*k) = skip_quote(splits[(*i)], (*k));
	while (splits[(*i)][(*k)] != '|' && splits[(*i)][(*k)] != '\0'
			&& splits[(*i)][(*k)] != '<' && splits[(*i)][(*k)] != '>'
			&& splits[(*i)][(*k)] != '&')
			(*k)++;
	return (old_k);
}

static void	set_start(int *start, int *k, int add)
{
	(*start) = (*k);
	(*k) = (*k) + add;
}

void	acutal_split(char **splits, char **words, int *i, int *no_word)
{
	int	start;
	int	k;

	k = 0;
	while (splits[(*i)][k] != '\0')
	{
		start = skip(splits, i, &k);
		if (k > start)
			words[(*no_word)++] = ft_substr(splits[(*i)], start, k - start);
		if (splits[(*i)][k] == '\0')
			break ;
		if (double_operator_found(splits[(*i)][k], splits[(*i)][k + 1]))
		{
			set_start(&start, &k, 2);
			words[(*no_word)++] = substr_skip(splits, start, &k, i);
		}
		else if (splits[(*i)][k] == '|' || splits[(*i)][k] == '>'
				|| splits[(*i)][k] == '<')
		{
			set_start(&start, &k, 1);
			words[(*no_word)++] = substr_skip(splits, start, &k, i);
		}
		else
			k++;
	}
}
