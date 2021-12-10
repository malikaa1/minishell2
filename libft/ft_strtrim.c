/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 16:07:10 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/18 02:10:56 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size;
	char		*ptr;

	if (s1 == NULL)
		return (NULL);
	if (*s1 == '\0' || set == NULL)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size - 1 > 0 && ft_strchr(set, s1[size - 1]))
		size--;
	if (size == 0)
		return (ft_calloc(1, 1));
	ptr = ft_substr(s1, 0, size + 1);
	return (ptr);
}
