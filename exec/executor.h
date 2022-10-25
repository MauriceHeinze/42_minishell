/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:19:47 by rpohl             #+#    #+#             */
/*   Updated: 2022/10/24 15:37:11 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/types.h>

typedef struct s_exec {
	int		pipe[2];
	pid_t	*pids;
	int		status;
	// temp
	int		pipes;
	int		x;
	
}				t_exec;

#endif