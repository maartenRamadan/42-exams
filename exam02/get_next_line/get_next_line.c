/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mramadan <mramadan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 11:45:18 by mramadan      #+#    #+#                 */
/*   Updated: 2021/05/07 23:20:12 by Marty         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (str + 1);
		str++;
	}
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	s3 = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (0);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		s3[i] = s2[i2];
		i2++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

int		write_line(char *str, char **line, int ret)
{
	int i;

	i = 0;
	*line = malloc(sizeof(char) * ft_strlen2(str) + 1);
	if (!*line)
	{
		free(str);
		return (-1);
	}
	while (str[i] && str[i] != '\n')
	{
		(*line)[i] = str[i];
		i++;
	}
	(*line)[i] = '\0';
	if (ret == 0)
		free(str);
	return (0);
}

char	*get_that_line(char *str, char **line)
{
	int		check;
	char	*tmp;

	check = write_line(str, line, 1);
	if (check == -1)
		return (0);
	tmp = str;
	str = ft_strdup(ft_strchr(str, '\n'));
	free(tmp);
	if (!str)
		return (0);
	return (str);
}

char	*read_more(char *str, int *ret)
{
	char buf[BUF_SIZE + 1];
	char *tmp;

	*ret = read(0, buf, BUF_SIZE);
	if (*ret < 0)
	{
		free(str);
		return (0);
	}
	buf[*ret] = '\0';
	tmp = str;
	str = ft_strjoin(str, buf);
	free(tmp);
	if (!str)
		return (0);
	return (str);
}

int		get_next_line(char **line)
{
	static char *str;
	int			ret;

	if (!str)
		str = ft_strdup("");
	if (!str)
		return (-1);
	if (ft_strchr(str, '\n'))
	{
		str = get_that_line(str, line);
		if (!str)
			return (-1);
		return (1);
	}
	else
		str = read_more(str, &ret);
	if (!str)
		return (-1);
	if (ret == 0)
		return (write_line(str, line, 0));
	return (get_next_line(line));
}

int		main(void)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(&line);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
