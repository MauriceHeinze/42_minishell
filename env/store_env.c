/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:16:36 by mheinze           #+#    #+#             */
/*   Updated: 2022/12/11 21:28:34 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_full_env_line(char *env[], int *i, int *k)
{
	(*k) = 0;
	while (env[(*i)][(*k)] != '\0')
		(*k)++;
	return (ft_substr(env[(*i)], 0, (*k)));
}

static char	*get_env_name(char *env[], int *i, int *k)
{
	(*k) = 0;
	while (env[(*i)][(*k)] != '\0' && env[(*i)][(*k)] != '=')
		(*k)++;
	return (ft_substr(env[(*i)], 0, (*k)));
}

static char	*get_env_content(char *env[], int *i, int *k, int last_pos)
{
	while (env[(*i)][(*k)] != '\0')
		(*k)++;
	return (ft_substr(env[(*i)], last_pos, (*k)));
}

static t_var	*setup_next_var(t_var *var)
{
	var->next = setup_var_node();
	var = var->next;
	return (var);
}

t_var	*store_env(char *env[])
{
	t_var	*var;
	t_var	*head;
	int		last_pos;
	int		i;
	int		k;

	var = setup_var_node();
	head = var;
	last_pos = 0;
	i = 0;
	while (env == NULL && env[i])
	{
		var->not_splitted = get_full_env_line(env, &i, &k);
		var->name = get_env_name(env, &i, &k);
		last_pos = k;
		if (env[i][k] == '=')
			k++;
		last_pos = k;
		var->content = get_env_content(env, &i, &k, last_pos);
		if (env[i + 1] != NULL)
			var = setup_next_var(var);
		i++;
	}
	return (head);
}
