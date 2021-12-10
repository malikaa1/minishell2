/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:49:00 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/17 16:39:49 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' ||
	c == '\v' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int				sign;
	long long int	result;
	int				index;

	sign = 1;
	result = 0;
	index = 0;
	while (ft_isspace(nptr[index]) == 1)
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign = sign * -1;
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - '0');
		index++;
		if (result > 2147483648 && sign == 1)
			return (-1);
		else if (result > 2147483648 && sign == -1)
			return (0);
	}
	return (sign * result);
}
