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

static int	double_operator_found(char a, char b)
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

static int	get_total_words(char **splitted_line)
{
	int		i;
	int		total_words;

	i = 0;
	total_words = 1;
	while (splitted_line[i] != NULL)
	{
		total_words += count_words_operators(splitted_line[i]);
		i++;
	}
	return (total_words);
}

char	**split_subline(char **splitted_line)
{
	int		i;
	int		k;
	int		start;
	int		no_word;
	char	**words;

	i = 0;
	no_word = 0;
	start = 0;
	words = malloc(sizeof(char *) * get_total_words(splitted_line));
	if (!words)
		return (NULL);
	while (splitted_line[i] != NULL)
	{
		if (count_words_operators(splitted_line[i]) == 1)
		{
			words[no_word] = ft_strdup(splitted_line[i]);
			if (!words)
				return (NULL);
			no_word++;
		}
		else
		{
			k = 0;
			while (splitted_line[i][k] != '\0')
			{
				start = k;
				if (splitted_line[i][k] == '\"' || splitted_line[i][k] == '\'')
					k = skip_quote(splitted_line[i], k);
				while (!ft_strchr("|<>&", splitted_line[i][k]) && splitted_line[i][k] != '\0')
					k++;
				if (k > start)
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
				if (double_operator_found(splitted_line[i][k], splitted_line[i][k + 1]))
				{
					start = k;
					k += 2;
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
				}
				else if ((splitted_line[i][k] == '<') || (splitted_line[i][k]  == '>') || (splitted_line[i][k]  == '|'))
				{
					start = k;
					k++;
					words[no_word++] = ft_substr(splitted_line[i], start, k - start);
					if (splitted_line[i][k] == ' ')
						k++;
				}
				else
					k++;
			}
		}
		i++;
	}
	words[get_total_words(splitted_line) - 1] = NULL;
	return (words);
}