/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-moel <tle-moel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:05:26 by tle-moel          #+#    #+#             */
/*   Updated: 2024/07/24 10:50:19 by tle-moel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	char	quote;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
		{
			if (*s == '\'' || *s == '\"')
			{
				quote = *s++;
				while (*s && *s != quote)
					s++;
			}
			if (*s)
				s++;
		}
	}
	return (count);
}

void	word_split_condition(size_t *count, int *i, char const *s)
{
	if (s[*i] == '\'')
	{
		(*count)++;
		(*i)++;
		while (s[*i] != '\'')
		{
			(*count)++;
			(*i)++;
		}
	}
	else if (s[*i] == '\"')
	{
		if (s[*i] == '\"')
		{
			(*count)++;
			(*i)++;
			while (s[*i] != '\"')
			{
				(*count)++;
				(*i)++;
			}
		}
	}
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
		word_split_condition(&count, &i, s);
		count++;
		i++;
	}
	word = (char *)malloc(sizeof(char) * count + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, count + 1);
	return (word);
}

int	ms_split_condition(char const *s, char c)
{
	int	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
	{
		if (*(s + i) == '\'')
		{
			i++;
			while (*(s + i) != '\'')
				i++;
		}
		else if (*(s + i) == '\"')
		{
			i++;
			while (*(s + i) != '\"')
				i++;
		}
		i++;
	}
	return (i);
}

char	**ms_split(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;

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
		j = ms_split_condition(s, c);
		s = s + j;
	}
	arr[i] = NULL;
	return (arr);
}
