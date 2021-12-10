/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:02:57 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/15 00:36:54 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] != '\0' && j < n)
	{
		s1[i] = s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	retour;

	retour = ft_strlen(src);
	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	if (i < size)
		retour = retour + i;
	else
		retour = retour + size;
	if ((int)(size - ft_strlen(dest) - 1) > 0)
		ft_strncat(dest, (char *)src, size - ft_strlen(dest) - 1);
	return (retour);
}
