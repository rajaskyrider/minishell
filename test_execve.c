/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:21:22 by rpandipe          #+#    #+#             */
/*   Updated: 2024/06/05 16:44:04 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



void	main(int argc, char **argv, char **env)
{
#if 0
	char	*args[] = {"sh", 
						"-c",
						"echo \"The date next year will be `date -d \\\"$(date +'%Y-%m-%d') next year\\\"`\"",
						NULL
					  };
	char	*cmd = "/bin/sh";
#endif
#if 1
	char *args[] = { "echo", "`date`", NULL };
	char	*cmd = "/bin/echo";
#endif

	const char *buf = getenv("(date)");
	execve(cmd, args, NULL);
	printf("%s", buf);
	perror("execve failure");
	exit(EXIT_FAILURE);
}
