/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mheinze <mheinze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:54:06 by mheinze           #+#    #+#             */
/*   Updated: 2022/04/14 15:24:51 by mheinze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list_item;
	t_list	*tmp_list_item;

	if (!lst || !del)
		return ;
	list_item = *lst;
	while (list_item)
	{
		tmp_list_item = list_item -> next;
		del(list_item -> content);
		free(list_item);
		list_item = tmp_list_item;
	}
	*lst = NULL;
}
