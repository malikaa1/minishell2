/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:42:49 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/14 23:36:33 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int		i;
	size_t	n;

	n = ft_strlen(s2);
	i = 0;
	if (s2[0] == 0)
		return ((char *)s1);
	while (s1[i] != 0 && i + n - 1 < len)
	{
		if (ft_strncmp(s1 + i, s2, n) == 0)
		{
			return ((char *)(s1 + i));
		}
		else
		{
			i++;
		}
	}
	return (NULL);
}
