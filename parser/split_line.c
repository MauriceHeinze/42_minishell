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

char	**split_line(char *str)
{
	int		i;
	int		start;
	int		no_word;
	int		total_words;
	char	**words;
	char	*tmp;

	i = 0;
	start = 0;
	no_word = 0;
	tmp = ft_strtrim(str, " ");
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	free(str);
	str = tmp;
	total_words = count_words(str);
	words = malloc(sizeof(char *) * (total_words + 1));
	if (!words)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		start = i;
		while (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
			i++;
		if (i > start)
		{
			if (ft_strchr(" 	", str[i]))
				i++;
			words[no_word++] = ft_substr(str, start, i - start);
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i + quote_length(str[i], str, i) + 2] == ' ')
			{
				i = i + quote_length(str[i], str, i) + 2;
				words[no_word++] = ft_substr(str, start, i - start + 1);
			}
			else
			{
				i = i + quote_length(str[i], str, i) + 1;
				words[no_word++] = ft_substr(str, start, i - start + 1);
			}
		}
		i++;
	}
	free(tmp);
	tmp = NULL;
	words[no_word] = NULL;
	return (words);
}
