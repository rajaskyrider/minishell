/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 09:31:34 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/07 11:31:13 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ms_env(t_ms *shell)
{
    t_envlst    *envlst;

    envlst = shell->environ;
    while (envlst)
    {
        ft_putstr_fd(envlst->key, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(envlst->value, 1);
        ft_putstr_fd("\n", 1);
        envlst = envlst->next;
    }
}

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
        if (key && value)
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
    t_envlst    *ptr;
    t_envlst    *env_node;

    if (*environ == NULL)
    {
        *environ = malloc(sizeof(t_envlst));
        if (*environ == NULL)
            return ;
        (*environ)->key = key;
        (*environ)->value = value;
        (*environ)->next = NULL;
        (*environ)->prev = NULL;
        return ;
    }
    env_node = malloc(sizeof(t_envlst));
    if (env_node == NULL)
        return ;
    env_node->key = key;
    env_node->value = value;
    env_node->next = NULL;
    ptr = *environ;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = env_node;
    env_node->prev = ptr;
}
