/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:33:17 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/23 13:00:46 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Echo the STRING(str) to standard output.
// If n is true do not output the trailing newline
// If str is empty printf nothing an do not throw error
void	echo(char *str, int n)
{
	if (str != NULL)
	{
		while (*str != '\0')
			write(1, str++, 1);
	}
	if (!n)
		write(1, "\n", 1);
}

// What about variables like $USER?
// change working relative or aboslute
// Relative paths can use . to stay in the current dir and .. to go one dir up
// WHat error management is needed? e.g. dir not found
// does stringcompare recognize the null temrinator int the string? This is a must 
void	cd(char *dir)
{
	if (chdir (dir) == -1)
		perror("");
}

// Print the full filename of the current working directory.
void	pwd()
{
	char	*cwd;
	
	if (getcwd(cwd, 0) == NULL)
		perror("");
	ft_putstr_fd(cwd, 1);
	free(cwd);
}


