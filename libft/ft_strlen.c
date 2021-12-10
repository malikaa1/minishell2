/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:39:46 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/11 18:57:58 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char	*ptr;
	size_t		i;

	ptr = str;
	i = 0;
	if (ptr == NULL)
		return 0;
	while (ptr[i] != '\0')
	{
		i++;
	}
	return (i);
}
