/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:55:52 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/15 19:04:26 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_exit_code(int exit_code)
{
	char *exit_code_str;

	exit_code_str = ft_itoa(exit_code);
	add_env(program->envp, "?", ft_strdup(exit_code_str));
	free(exit_code_str);
}