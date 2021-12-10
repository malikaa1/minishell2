/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:03:48 by ybesbes           #+#    #+#             */
/*   Updated: 2021/12/02 13:03:54 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *dollar_between_quotes(char **str, char *com, int char_to_extract, int char_to_add)
{
    int i;
    int j;
    int k;
    int tmp;
    char *env;

    k = 0;
    i = 0;
    j = 0;
    tmp = 0;

    env = malloc(sizeof(char) * (ft_strlen(com) - char_to_extract + char_to_add + 1));
    if (env == NULL)
        return NULL;
    while (com[i] != '\0')
    {
        if (com[i] == '$' && is_it_between_simple_quotes(com, i) == 0
            && ft_isspace(com[i + 1]) != 1 && com[i + 1] != '\0')
        {
            i++;
            while (ft_isalnum(com[i]) == 1)
                i++;
            if (str != NULL && str[tmp] != NULL)
            {
                k = 0;
                while (str[tmp][k] != '\0')
                {
                    env[j] =  str[tmp][k];
                    j++;
                    k++;
                }
                tmp++;
            }
        }
        else
        {
            env[j] = com[i];
            i++;
            j++;
        }
    }
    env[j] = '\0';
    return (env);
}