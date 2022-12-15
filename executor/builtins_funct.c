/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_funct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralf <ralf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 13:49:58 by rpohl             #+#    #+#             */
/*   Updated: 2022/12/15 11:01:01 by ralf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	exit_sub_handler(t_node *node, char *check_input, int fd)
{
	ft_putstr_fd("exit\n", fd);
	if (*check_input == ' ')
	{
		exec_error(EXIT_NUM_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
		return (1);
	}
	builtin_error(EXIT_ARG_ERROR, &(node->full_cmd[ft_strlen("exit") + 1]));
	exit_shell(255);
	return (0);
}

static void	exit_direct(int fd)
{
	ft_putstr_fd("exit\n", fd);
	exit_shell(0);
}

int	exit_pre_handler(t_node *node, int fd)
{
	char	*check_input;

	if (ft_strlen("exit") == ft_strlen(node->full_cmd))
		exit_direct(fd);
	else
	{
		check_input = &(node->full_cmd[ft_strlen("exit") + 1]);
		if (*check_input == '+' || *check_input == '-')
			check_input++;
		while (*check_input != '\0')
		{
			if (*check_input >= '0' && *check_input <= '9')
				check_input++;
			else
			{
				if (exit_sub_handler(node, check_input, fd) == 1)
					return (1);
			}
		}
		ft_putstr_fd("exit\n", fd);
		exit_shell(ft_atoi(&(node->full_cmd[ft_strlen("exit") + 1])));
	}
	return (0);
}
