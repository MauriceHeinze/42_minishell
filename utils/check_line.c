/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:08:32 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/19 12:06:20 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	'
		|| line[i] == '.' || line[i] == ';'
		|| line[i] == '\"' || line[i] == '\''
		|| line[i] == '\t')
		i++;
	if (line[i] == '\0')
	{
		track_history(line);
		free(line);
		line = NULL;
		return (0);
	}
	return (1);
}
