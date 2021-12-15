/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:03:48 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/15 22:05:30 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void copy_to(char *str, char *dest, int *dest_start)
{
    int k;
    
    k = 0;
    while (str[k] != '\0')
    {
        dest[*dest_start] = str[k++];
        *dest_start += 1;
    }
}

void dollar_between_quotes(char **str, char *com, char *buff)
{
    int i;
    int j;
    int tmp;

    i = 0;
    j = 0;
    tmp = 0;

    while (com[i] != '\0')
    {
        if (com[i] == '$' && is_it_between_simple_quotes(com, i) == 0 && ft_isspace(com[i + 1]) != 1 && com[i + 1] != '\0')
        {
            i++;
            while (ft_isalnum(com[i]) == 1)
                i++;
            if (str != NULL && str[tmp] != NULL)
                copy_to(str[tmp++], buff, &j);
        }
        else
            buff[j++] = com[i++];
    }
    buff[j] = '\0';
}