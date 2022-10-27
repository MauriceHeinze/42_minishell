/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohl <rpohl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:30:40 by rpohl             #+#    #+#             */
/*   Updated: 2022/05/06 09:48:38 by rpohl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_int_length(int n)
{
	int	length;

	length = 1;
	if (n < 0)
		length++;
	while (n / 10 != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static int	check_sign(int n)
{
	if (n >= 0)
		return (0);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	int		length;
	int		num;
	char	*cp;
	int		neg;

	neg = check_sign(n);
	num = n;
	length = check_int_length(n);
	cp = malloc(length + 1);
	if (!cp)
		return (NULL);
	*(cp + length) = 0;
	while (length > 0)
	{
		if (neg == 0)
			*(cp + length - 1) = (num % 10) + 48;
		else
			*(cp + length - 1) = (num % 10 * (-1)) + 48;
		length--;
		num /= 10;
	}
	if (n < 0)
		*cp = '-';
	return (cp);
}
