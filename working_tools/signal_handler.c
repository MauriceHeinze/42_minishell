/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/17 13:45:33 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	signal_quit(int sig)
{
	printf("Quit!");
}

static void	signal_interrupt(int sig)
{
	printf("Interrupt!");
}

void	setup_signal_handler(void)
{
	signal(SIGQUIT, signal_quit); /* Ctrl-\ */
	signal(SIGINT, signal_interrupt); /* Ctrl-C */
}