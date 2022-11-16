/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/11/16 17:02:48 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	special_error(int error)
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

void	exec_error(int error, char *s)
{
	set_exit_code(error);
	if (error == EXPORT_ERROR)
		printf("minishell: export: `%s': not a valid identifier\n", s);
	else if (error == EXIT_ARG_ERROR)
		printf("minishell: exit: %s: numeric argument required\n", s);
	else if (error == CMD_ERROR)
		printf("minishell: command: %s: not found\n", s);
	else if (error == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", s);
	else if (error == PATH_ERROR)
		printf("minishell: %s: No such file or directory\n", s);
	else if (error == UNSET_ERROR)
		printf("minishell: unset: `%s': not a valid identifier\n", s);
	else if (error == PERMISSION_ERROR)
		printf("minishell: %s: Permission denied\n", s);
	else if (error == EMPTY_KEY_ERROR)
		printf("minishell: cd: %s not set\n", s);
}