/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inter.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mramadan <mramadan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/07 09:37:34 by mramadan       #+#    #+#                */
/*   Updated: 2020/01/20 16:57:35 by mramadan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int i;
	int i2;
	char used[255];

	i = 0;
	i2 = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (argv[1][i])
	{
		if (ft_strchr(argv[2], argv[1][i]))
		{
			write(1, &argv[1][i], 1);
			used[i2] = argv[1][i];
			i++;
			i2++;
		}
		else
			i++;
		while (ft_strchr(used, argv[1][i]))
			i++;
	}
	write(1, "\n", 1);
}
