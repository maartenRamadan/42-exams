/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mramadan <mramadan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:56:54 by mramadan       #+#    #+#                */
/*   Updated: 2020/01/14 10:56:38 by mramadan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 1

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

char	*write_line(char *buf, char **line)
{
	char *tmp;
	int i;

	i = 0;
	while ((*line)[i])
		i++;
	tmp = malloc(i + 2);
	if (!tmp)
		return (0);
	i = 0;
	while ((*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = buf[0];
	tmp[i + 1] = '\0';
	free(*line);
	return (tmp);
}

int		get_next_line(char **line)
{
	int ret;
	char buf[1];

	*line = malloc(1);
	if (!*line)
		return (-1);
	(*line)[0] = '\0';
	while (1)
	{
		ret = read(0, buf, BUF_SIZE);
		if (ret == -1 || ret == 0 || buf[0] == '\n')
			return (ret);
		*line = write_line(buf, line);
		if (!*line)
			return (-1);
	}
}

int		main(void)
{
	int ret;
	char *line;

	ret = 1;
	while (ret)
	{
		ret = get_next_line(&line);
		printf("%s\n", line);
	}
	return (0);
}

