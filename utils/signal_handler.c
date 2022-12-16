/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/16 12:20:32 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_interrupt_default(int sig)
{
	(void)sig;
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
	(void)sig;
	kill(0, SIGQUIT);
}

void	child_signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_interrupt_child);
}
