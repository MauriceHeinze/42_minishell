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

char	*expand_variable(char *input_str, int start, int i)
{
	char	*var_name;

	var_name = ft_substr(input_str, start, i - start);
	input_str = str_remove(input_str, start, i - start + 1);
	if (get_env(program->envp, var_name))
		input_str = str_add(input_str, get_env(program->envp, var_name), start);
	free(var_name);
	return (input_str);
}

char	*expand_variables(char *input_str)
{
	int		i;
	int		start;
	int		double_quote;

	i = 0;
	double_quote = 0;
	// get number of chars of variables
	while (input_str[i] != '\0')
	{
		if (input_str[i] == '\'' && double_quote == 0)
			i = skip_quote(input_str, i);
		else if (input_str[i] == '$' && (ft_isalpha(input_str[i + 1]) || ft_strchr("?_", input_str[i + 1])))
		{
			i++;
			start = i;
			while (input_str[i] != '\0' && input_str[i] != '/' && (ft_isalpha(input_str[i]) || ft_isalnum(input_str[i]) || ft_strchr("?_", input_str[i])))
				i++;
			input_str = expand_variable(input_str, start, i);
			i = 0;
			start = 0;
		}
		else if (input_str[i] == '~' && (ft_strchr("/ 	", input_str[i + 1])))
		{
			i++;
			start = i;
			input_str = str_remove(input_str, start, i - start + 1);
			input_str = str_add(input_str, get_env(program->envp, "HOME"), start);
			i = 0;
			start = 0;
		}
		else
		{
			if (input_str[i] == '\"' && double_quote == 0)
				double_quote = 1;
			else if (input_str[i] == '\"' && double_quote == 1)
				double_quote = 0;
			i++;
		}
	}
	return (input_str);
}