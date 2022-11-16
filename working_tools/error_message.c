/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/16 15:20:36 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(int error)
{
	set_exit_code(error);
	if (error == SINGLE_QUOTE_MISSING)
		printf("minishell: Syntax Error. Missing '\n");
	else if (error == DOUBLE_QUOTE_MISSING)
		printf("minishell: Syntax Error. Missing \"\n");
	else if (error == EXIT_ERROR)
		printf("minishell: exit: too many arguments\n");
	else if (error == INVALID_PATH)
		printf("minishell: No such file or directory");
	else if (error == OLDPWD_ERROR)
		printf("minishell: cd: OLDPWD not set\n");
	else if (error == ENV_ERROR)
		printf("minishell: env: too many arguments\n");
}