/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:56:53 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:46:48 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		length;

	length = 0;
	while (s1[length])
	{
		length++;
	}
	result = malloc((length + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	*(result + length) = 0;
	while (length > 0)
	{
		*(result + length - 1) = *(s1 + length - 1);
		length--;
	}
	return (result);
}
