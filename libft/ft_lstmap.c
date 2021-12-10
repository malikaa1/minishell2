/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 22:17:56 by ybesbes           #+#    #+#             */
/*   Updated: 2020/05/24 23:44:05 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*element;

	if (lst == NULL || !(new = ft_lstnew((*f)(lst->content))))
		return (NULL);
	lst = lst->next;
	element = new;
	while (lst)
	{
		ft_lstadd_back(&new, ft_lstnew((*f)(lst->content)));
		if (!(element = element->next))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new);
}
