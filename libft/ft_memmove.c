/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:49:48 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/19 19:29:27 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (s2 > s1)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			s1[n - 1] = s2[n - 1];
			n--;
		}
	}
	return (dest);
}
