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

int	count_words(char *input_str)
{
	int	i;
	int	start;
	int	no_word;

	start = 0;
	i = 0;
	no_word = 0;
	while (input_str[i] != '\0')
	{
		start = i;
		while (!ft_strchr("\'\" 	", input_str[i]) && input_str[i] != '\0')
			i++;
		if (i > start)
		{
			if (ft_strchr(" 	", input_str[i]))
				i++;
			no_word++;
			continue;
		}
		if (input_str[i] == '\'' || input_str[i] == '\"')
		{
			if (input_str[i + quote_length(input_str[i], input_str, i) + 2] == ' ')
			{
				i = i + quote_length(input_str[i], input_str, i) + 2;
				no_word++;
			}
			else
			{
				i = i + quote_length(input_str[i], input_str, i) + 1;
				no_word++;
			}
		}
		i++;
	}
	return (no_word);
}
