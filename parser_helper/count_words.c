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

static int	count_spaces(char *input_str)
{
	int	i;
	int	no_spaces;
	int	count;

	i = 0;
	no_spaces = 0;
	count = 1;
	while (input_str[i] != '\0' && ft_strchr(" 	", input_str[i]))
		i++;
	while (input_str[i] != '\0')
	{
		if (ft_strchr("\'\"", input_str[i]))
		{
			if (i > 0 && !ft_strchr(" 	", input_str[i - 1])) // if previous char isn't a space
			{
				no_spaces++;
				if (!ft_strchr("\"\'", input_str[i]))
					i++;
			}
			i = skip_quote(input_str, i); // jumps to char after quote
			if (!ft_strchr(" 	", input_str[i])) // if this char is no space, count up
				no_spaces++;
		}
		if (ft_strchr(" 	", input_str[i])) // if char is space, count up
		{
			while (input_str[i + 1] == ' ')
				i++;
			if (input_str[i + 1] == '\0')
				break;
			no_spaces++;
		}
		i++;
	}
	if (input_str[i] == '\0')
		no_spaces++;
	return (no_spaces);
}

int	count_words(char *input_str)
{
	int	no_spaces;

	if (ft_strlen(input_str) == 0)
		return (0);
	no_spaces = count_spaces(input_str);
	if (ft_strlen(input_str) > 0 && no_spaces == 0)
		return (1);
	else
		return (no_spaces);
}
