/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:20:08 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/17 21:40:04 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src == NULL)
	{
		dest = NULL;
		return (0);
	}
	while (i < size && *src != '\0')
	{
		*dest++ = *src++;
		i++;
	}
	if (i < size)
	{
		*dest = '\0';
		return (i);
	}
	else if (size > 0)
	{
		*(dest - 1) = '\0';
		return (i + ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}
