/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/04 21:08:50 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*copy_quote(char found_quote, char *input_str, int pos)
{
	int		k;
	char	*quote;

	k = 0;
	quote = malloc(sizeof(char) * ft_strlen(input_str));
	// printf("Test: %c\n", input_str[pos]);
	quote[k++] = input_str[pos++];
	while (input_str[pos] != '\0')
	{
		if (input_str[pos] == found_quote)
			break ;
		else
		{
			if (input_str[pos] == '\\')
				quote[k] = special_char(input_str, pos++);
			else
				quote[k] = input_str[pos++];
			k++;
		}
	}
	quote[k] = '\0';
	return (quote);
}
