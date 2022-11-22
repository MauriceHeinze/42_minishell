/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/22 15:28:50 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_exit_code(int exit_code)
{
	char *exit_code_str;

	program->status = exit_code;
	exit_code_str = ft_itoa(exit_code);
	add_env(program->envp, "?", ft_strdup(exit_code_str));
	free(exit_code_str);
}

void	exit_shell(int error_code)
{
	set_exit_code(error_code);
	special_error(error_code);
	// free all allocated resources
		// free hdocs
		// free tokens
		// free builtins
		// free envp
		// free all resources
	exit(1);
}
