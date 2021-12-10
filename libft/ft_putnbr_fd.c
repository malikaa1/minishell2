/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 19:43:09 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/11 20:04:33 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_positif_fd(int n, int fd)
{
	int		a;
	char	c;

	if (n / 10 != 0)
	{
		ft_putnbr_positif_fd(n / 10, fd);
	}
	a = n % 10;
	if (a < 0)
		a = -a;
	c = a + '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putnbr_positif_fd(n, fd);
}
