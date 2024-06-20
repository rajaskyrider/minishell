/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:26 by tle-moel          #+#    #+#             */
/*   Updated: 2024/06/20 11:10:05 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
		{
			if (*s == '\'')
			{
				s++;
				while (*s != '\'')
					s++;
			}
			else if (*s == '\"')
			{
				s++;
				while (*s != '\"')
					s++;
			}
			s++;
		}
	}
	return (count);
}

static char	*word_split(char const *s, char c)
{
	size_t	count;
	int		i;
	char	*word;

	count = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'')
		{
			count++;
			i++;
			while (s[i] != '\'')
			{
				count++;
				i++;
			}
		}
		else if (s[i] == '\"')
		{
			if (s[i] == '\"')
			{
				count++;
				i++;
				while (s[i] != '\"')
				{
					count++;
					i++;
				}
			}
		}
		count++;
		i++;
	}
	word = (char *)malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, count + 1);
	return (word);
}

char	**ms_split(char const *s, char c)
{
	char	**arr;
	int		i;

	i = 0;
	arr = (char **)malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			arr[i] = word_split(s, c);
			if (!arr[i])
				return (NULL);
			i++;
		}
		while (*s && *s != c)
		{
			if (*s == '\'')
			{
				s++;
				while (*s != '\'')
					s++;
			}
			else if (*s == '\"')
			{
				s++;
				while (*s != '\"')
					s++;
			}
			s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}