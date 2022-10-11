/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/11 11:15:17 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_length(char found_quote, char *input_str, int pos)
{
	int		quote_len;
	char	*quote;

	quote = copy_quote(found_quote, input_str, pos);
	quote_len = ft_strlen(quote);
	free(quote);
	return (quote_len);
}
