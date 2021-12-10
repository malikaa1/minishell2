/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 20:49:53 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/17 15:23:46 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest_local;
	char	*src_local;

	i = 0;
	dest_local = (char *)dest;
	src_local = (char *)src;
	if (!dest && !src)
	{
		return (NULL);
	}
	while (i < n)
	{
		dest_local[i] = src_local[i];
		i++;
	}
	return (dest);
}
