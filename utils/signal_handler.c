/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 23:38:10 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_interrupt_default(int sig)
{
	write (1, "\n", 1);
	rl_free_line_state();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	default_signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_interrupt_default);
}

static void	signal_interrupt_child(int sig)
{
	kill(0, SIGQUIT);
}

void	child_signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_interrupt_child);
}
