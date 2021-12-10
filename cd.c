/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrahmani <mrahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:37:26 by mrahmani          #+#    #+#             */
/*   Updated: 2021/10/28 15:56:20 by mrahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(char *arg)
{
    char *path;

    if (ft_strncmp(arg, "~/", 2) == 0)
        path = ft_substr(arg, 2, (ft_strlen(arg) - 2));
    else
        path = ft_strdup(arg);
    return (path);
}

int home_path()
{
    char *default_dir;
    int ret;

    default_dir = ft_strjoin("/home/", getenv("USER"));
    ret = chdir(default_dir);
    if (default_dir != NULL)
        free(default_dir);
    return (ret);
}

int change_path(char *path)
{
    int ret;
    DIR *d;

    d = opendir(path);
    if (d == NULL)
    {
        printf("cd: %s: No such file or directory\n", path);
        return (-1);
    }
    ret = chdir(path);
    if (ret < 0)
    {
        printf("lol\n");
        perror("cd ");
        closedir(d);
        return (-1);
    }
    closedir(d);
    return (ret);
}

int ft_cd(char **arg)
{
    char *path;
    int ret;

    if (arg[1] != NULL && arg[2] != NULL)
    {
        printf("cd: too many arguments\n");
        return (1);
    }
    if (arg[1] == NULL || (ft_strcompare(arg[1], "~") == 1))
        return (ret = home_path());
    path = get_path(arg[1]);
    ret = change_path(path);
    if (path != NULL)
        free(path);
    return (ret);
}