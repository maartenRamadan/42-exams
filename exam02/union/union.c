/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   union.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mramadan <mramadan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 09:37:42 by mramadan       #+#    #+#                */
/*   Updated: 2020/01/20 16:57:24 by mramadan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		ft_strchr(char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char used[255];
	int i;
	int i2;

	i = 0;
	i2 = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		write(1, &argv[1][i], 1);
		used[i2] = argv[1][i];
		i++;
		i2++;
		while (ft_strchr(used, argv[1][i]))
			i++;
	}
	i = 0;
	while (argv[2][i])
	{
		if (ft_strchr(used, argv[2][i]))
			i++;
		else
		{
			write(1, &argv[2][i], 1);
			used[i2] = argv[2][i];
			i2++;
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}


