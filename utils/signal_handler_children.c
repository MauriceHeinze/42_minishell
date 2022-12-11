/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_children.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 21:07:22 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_interrupt_child(int sig)
{
	// >> kill process <<
	// write (1, "\n", 1);
	// rl_free_line_state();
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	setup_signal_handler_child(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_interrupt_child);
}
