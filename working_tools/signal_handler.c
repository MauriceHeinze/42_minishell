/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/17 14:43:01 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// should do nothing
static void	signal_quit(int sig)
{
	// should do nothing
}

// should return a new prompt
static void	signal_interrupt(int sig)
{
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handler(void)
{
	signal(SIGQUIT, signal_quit); /* Ctrl-\ */
	signal(SIGINT, signal_interrupt); /* Ctrl-C */
}


//  gcc ./src/main.c ./inc/minishell.h ./libft/libft.a ./working_tools/*.c -lreadline -L /goinfre/mheinze/.brew/opt/readline/lib -I /goinfre/mheinze/.brew/opt/readline/include

// -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include