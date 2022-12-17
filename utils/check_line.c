/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:08:32 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/17 18:22:29 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_line(char *line)
{
	int		i;
	char	*cmd;

	i = 0;
	while (line[i] == ' ' || line[i] == '	'
		|| line[i] == '.' || line[i] == ';'
		|| line[i] == '\"' || line[i] == '\''
		|| line[i] == '\t')
		i++;
	if (line[i] == '\0')
	{
		cmd = ft_strtrim(line, " 	");
		track_history(line);
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}
