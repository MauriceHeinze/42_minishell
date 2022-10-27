/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:10:19 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 18:01:28 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*vp;

	if (count != 0 && size != 0)
	{
		if (4294967295 / count < size || 4294967295 / size < count)
			return (NULL);
	}
	vp = malloc(count * size);
	if (vp == NULL)
		return (NULL);
	ft_bzero(vp, count * size);
	return (vp);
}
