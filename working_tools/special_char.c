/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:18 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/04 21:08:19 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	special_char(char *input_str, int pos)
{
	if (input_str[pos] == '\\')
	{
		if (input_str[pos + 1] == '\\')
			return ('\\');
		else if (input_str[pos + 1] == '\'')
			return ('\'');
		else if (input_str[pos + 1] == '\"')
			return ('\"');
		// else if (input_str[pos + 1] == 't')
		// 	return ('	');
		// else if (input_str[pos + 1] == 'n')
		// 	return ('\n');
		else if (input_str[pos + 1] == '\'')
			return ('\'');
	}
	return (input_str[pos]);
}