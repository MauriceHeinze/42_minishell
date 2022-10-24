/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/24 20:21:03 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	track_history(char *line)
{
	if (line == NULL)
		exit(0); // exit shell
	if (line[0] != '\0')
		add_history(line);
}