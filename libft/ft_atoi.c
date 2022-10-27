/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralf <ralf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:38:30 by rpohl             #+#    #+#             */
/*   Updated: 2022/08/01 17:53:26 by ralf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (1)
	{
		if (*(str + i) == '\t')
			i++;
		else if (*(str + i) == '\n')
			i++;
		else if (*(str + i) == '\r')
			i++;
		else if (*(str + i) == '\b')
			i++;
		else if (*(str + i) == '\v')
			i++;
		else if (*(str + i) == '\f')
			i++;
		else if (*(str + i) == ' ')
			i++;
		else
			break ;
	}
	return ((char *)(str + i));
}

void	throw_error(void)
{
	ft_putstr_fd("Error\n", 2, NULL);
	exit(EXIT_FAILURE);
}

static int	check_signs(const char *str)
{
	int	i;
	int	ret;
	int	num;

	i = 0;
	ret = 1;
	num = 0;
	while (*(str + i) == '+' || *(str + i) == '-')
	{
		if (*(str + i) == '-')
			ret = ret * -1;
		i++;
		num++;
		if (num > 1)
			return (0);
	}
	if (str[i] < 47 || str[i] > 57 || (str[i] == '0' && str[i + 1] == '\0'))
		throw_error();
	return (ret);
}

static void	check_int(int num, int nptr, int sign)
{
	if (sign == 1)
	{
		if (INT_MAX / 10 < num)
			throw_error();
		if (INT_MAX / 10 == num)
		{
			if (INT_MAX % 10 < nptr)
				throw_error();
		}
	}
	else
	{
		if (INT_MAX / 10 < num)
			throw_error();
		if (INT_MAX / 10 == num)
		{
			if (INT_MAX % 10 + 1 < nptr)
				throw_error();
		}
	}
}

int	ft_atoi(const char *str)
{
	int		num;
	char	*nptr;

	if (!check_signs(check_whitespace(str)) || *str == 0)
		throw_error();
	if (str == check_whitespace(str))
		nptr = (char *)str;
	else
		nptr = check_whitespace(str);
	if (*(nptr) == '+' || *(nptr) == '-')
		nptr++;
	num = 0;
	while (*nptr != 0)
	{
		if (*nptr < 47 || *nptr > 57)
			throw_error();
		check_int(num, *nptr - 48, check_signs(check_whitespace(str)));
		num = num * 10 + *nptr - 48;
		nptr++;
	}
	num = num * check_signs(check_whitespace(str));
	return (num);
}
