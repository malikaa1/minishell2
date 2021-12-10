/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybesbes <ybesbes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:55:05 by ybesbes           #+#    #+#             */
/*   Updated: 2021/11/29 13:55:14 by ybesbes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *to_lowercase(char *s1)
{
    char *s;
    int i;

    i = 0;
    s = ft_strdup(s1);
    while (s[i] != '\0')
    {
        s[i] = ft_tolower(s[i]);
        i++;
    }
    return (s);
}
void ft_swap(t_env *env1, t_env *env2)
{
    char *tmp_name;
    char *tmp_var;

    tmp_name = env1->name;
    tmp_var = env1->var;
    env1->name = env2->name;
    env1->var = env2->var;
    env2->name = tmp_name;
    env2->var = tmp_var;
}

int ft_sorted(t_env *list)
{
    t_env *tmp;
    char *s1;
    char *s2;
    int len;

    tmp = list;
    while (tmp != NULL)
    {
        if (tmp->next != NULL)
        {
            len = ft_strlen(tmp->var);
            s1 = to_lowercase(tmp->var);
            s2 = to_lowercase(tmp->next->var);
            if (ft_strncmp(s1, s2, len) > 0)
            {
                free(s1);
                free(s2);
                return (0);
            }
            free(s1);
            free(s2);
        }
        tmp = tmp->next;
    }
    return (1);
}
void  ft_sort(t_env *list)
{
    t_env *tmp;
    char *s1;
    char *s2;
    int len;

    tmp = list;
    while (ft_sorted(tmp) == 0)
    {
        while (tmp != NULL)
        {
            if (tmp->next != NULL)
            {
                len = ft_strlen(tmp->var);
                s1 = to_lowercase(tmp->var);
                s2 = to_lowercase(tmp->next->var);
                if (ft_strncmp(s1, s2, len) > 0)
                    ft_swap(tmp, tmp->next);
                free(s1);
                free(s2);
            }
            tmp = tmp->next;
        }
        tmp = list;
    }
}

int without_arg(t_env *env)
{
    char *tmp;
    t_env *env_list;

    env_list = env;
    ft_sort(env_list);
    if (env_list == NULL)
        return (0);
    while (env_list != NULL)
    {
        tmp = ft_strjoin("declare -x ", env_list->var);
        printf("%s\n", tmp);
        free(tmp);
        tmp = NULL;
        env_list = env_list->next;
    }
    return (1);
}