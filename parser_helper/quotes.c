/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/22 16:16:02 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_cmd_path.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mheinze <mheinze@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/04 21:08:49 by mheinze		   #+#	#+#			 */
/*   Updated: 2022/11/22 16:15:23 by mheinze		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../inc/minishell.h"

int	quote_length(char found_quote, char *input_str, int pos)
{
	int		k;

	k = 0;
	while (input_str[pos++] != '\0')
	{
		if (input_str[pos] == found_quote)
			break ;
		else
			k++;
	}
	return (k);
}

char	*remove_quotes(char *input_str)
{
	int	len;
	char *shortend;

	len = ft_strlen(input_str) - 1;
	if ((input_str[0] == '\'' && input_str[len] == '\'') ||
		(input_str[0] == '\"' && input_str[len] == '\"'))
	{
		shortend = ft_substr(input_str, 1, len - 1);
		free(input_str);
		return (shortend);
	}
	return (input_str);
}

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
