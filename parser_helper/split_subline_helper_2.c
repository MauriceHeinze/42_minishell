/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_subline_helper_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:41:59 by mheinze           #+#    #+#             */
/*   Updated: 2023/01/04 16:31:40 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	skip_space(char **splits, int *i, int *k)
{
	if (splits[(*i)][(*k)] == ' ' || splits[(*i)][(*k)] == '	')
		(*k)++;
}

char	*substr_skip(char **splits, int start, int *k, int *i)
{
	char	*subword;

	subword = ft_substr(splits[(*i)], start, (*k) - start);
	skip_space(splits, i, k);
	return (subword);
}
