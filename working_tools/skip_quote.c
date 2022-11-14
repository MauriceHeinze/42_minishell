/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/14 17:17:05 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_quote(char *input_str, int pos)
{
	char	found_quote;

	found_quote = input_str[pos];
	pos++;
	while (input_str[pos] != '\0')
	{
		if (input_str[pos] == found_quote)
			break ;
		else
			pos++;
	}
	return (pos + 1);
}
