/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 17:30:15 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/19 19:26:25 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		j;
	long	nbr;

	j = ft_count(n);
	nbr = n;
	str = malloc(sizeof(char) * (ft_count(n) + 1));
	if (str != NULL)
	{
		if (nbr < 0)
		{
			str[0] = '-';
			nbr = nbr * -1;
		}
		while (nbr / 10 != 0 && j >= 0)
		{
			str[j - 1] = (nbr % 10) + '0';
			nbr = nbr / 10;
			j--;
		}
		str[j - 1] = nbr + '0';
		str[ft_count(n)] = '\0';
	}
	return (str);
}
