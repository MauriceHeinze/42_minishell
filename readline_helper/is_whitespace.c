/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:55:52 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/15 18:55:53 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_whitespace(char *input_str)
{
	int	i;

	i = 0;

	while (input_str[i] == ' ' || input_str[i] == '	')
		i++;
	if (input_str[i] == '\0')
		return (1);
	else
		return (0);
}