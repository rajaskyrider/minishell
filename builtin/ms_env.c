/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:31:34 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/07 10:36:22 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst    *init_environ(char **env)
{
    t_envlst    *environ;
    int     i;
    char    *key;
    char    *value;

    environ = NULL;
    if (env == NULL)
        return (NULL);
    i = 0;
    while (env[i] != NULL)
    {
        key = extract_key(env[i]);
        value = extract_value(env[i]);
        update_envlst(key, value, &environ);
        i++;
    }
    return (environ);
}

char    *extract_key(char *env_line)
{
    int     i;

    i = 0;
    if (env_line == NULL)
        return (NULL);
    while (env_line[i] != '\0')
    {
        if (env_line[i] == '=')
             return (ft_substr(env_line, 0, i));
        i++;
    }
    return (NULL);
}

char    *extract_value(char *env_line)
{
    int     i;

    i = 0;
    if (env_line == NULL)
        return (NULL);
    while (env_line[i] != '\0')
    {
        if (env_line[i] == '=')
            return (ft_substr(env_line, i, ft_strlen(env_line) - i));
        i++;
    }
    return (NULL);
}

void    update_envlst(char *key, char *value, t_envlst **environ)
{
    
}
