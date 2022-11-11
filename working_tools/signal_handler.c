/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 21:08:49 by mheinze           #+#    #+#             */
/*   Updated: 2022/10/17 19:32:57 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ctrl_c(void)
{
	struct termios	att;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &saved);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	tcgetattr(STDIN_FILENO, &att);
	att.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &att);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

// should do nothing
static void	signal_quit()
{
	// should do nothing
}

// WATCH OUT! Check on different Imacs if ctrl-C is really not printing ++
// should return a new prompt
static void	signal_interrupt()
{
	ctrl_c();
	// write (1, "\n", 1);
	// rl_on_new_line();
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