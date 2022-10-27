/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:52:53 by rpohl             #+#    #+#             */
/*   Updated: 2022/07/27 20:01:38 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int num)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (head == NULL)
		return (0);
	head->num = num;
	head->n = NULL;
	return (head);
}
