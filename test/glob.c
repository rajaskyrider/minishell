/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:58:24 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/13 10:33:14 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int	match(char *pattern, char *filename)
{
	if (*pattern == 0)
		return (*filename == 0);
	if (*pattern == '*')
		return (match(pattern + 1, filename) || (*filename && match(pattern, filename + 1)));
	if (*pattern == *filename)
		return (match(pattern + 1, filename + 1));
	return (0);	
}

void	glob(char *pattern)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(".");
	if (!dp)
	{
		printf("Error");
		return ;
	}
	while ((entry = readdir(dp)))
	{
		if (match(pattern, entry->d_name))
			printf("File: %s\n", entry->d_name);
	}
}

int	main(int argc, char **argv)
{
	glob(argv[1]);

	return (0);
}