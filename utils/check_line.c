/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:08:32 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/16 16:10:19 by mheinze          ###   ########.fr       */
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
		|| line[i] == '\"' || line[i] == '\'')
		i++;
	if (line[i] == '\0')
	{
		cmd = ft_strtrim(line, " 	");
		track_history(line);
		printf("minishell: %s: command not found\n", cmd);
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}
