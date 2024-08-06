/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:28:37 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/06 15:27:18 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_strcasecmp(char *s1, char *s2)
{
	int		i;
	char	a;
	char	b;

	i = 0;
	while (s1[i] && s2[i])
	{
		a = s1[i];
		b = s2[i];
		if (a >= 'A' && a <='Z')
			a = a + 32;
		if (b >= 'A' && b <='Z')
			b = b + 32;
		if (a != b)
			return ((unsigned char)a - (unsigned char)b);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sort_args(char **args, int end)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;	
	while (i < end -1)
	{
		j = i + 1;
		while (j < end)
		{
			if (ms_strcasecmp(args[i], args[j]) > 0)
			{
				temp = args[i];
				args[i] = args[j];
				args[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*join_str(char *newcmd, int len, char **args)
{
	int		i;
	char	*cmd;

	i = 1;
	cmd = ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(cmd, args[0], ft_strlen(args[0]) + 1);
	free(args[0]);
	while (args[i])
	{
		ft_strlcat(cmd, " ", len + 1);
		ft_strlcat(cmd, args[i], len + 1);
		free(args[i]);
		i++;
	}
	free(args);
	free(newcmd);
	return (cmd);
}

char	*sort_cmd(char *newcmd)
{
	char	**args;
	int		count;
	int		len;

	count = 0;
	len = ft_strlen(newcmd);
	args = ms_split(newcmd, ' ');
	while (args[count])
		count++;
	if (count <= 1)
	{
		while (count > 0)
		{
			free(args[count]);
			count--;
		}
		free(args);
		return (newcmd);
	}
	sort_args(args, count);
	newcmd = join_str(newcmd, len, args);
	return (newcmd);
}

