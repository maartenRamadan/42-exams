/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_paint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Marty <Marty@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 09:43:38 by Marty         #+#    #+#                 */
/*   Updated: 2020/12/09 14:39:20 by mramadan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>

typedef struct	exam03
{
	int			w;
	int			h;
	char		cs;
	int			i;
	char		fill[256];
	float		x[256];
	float		y[256];
	float		radius[256];
	char		cc[256];
}				t_data;

int		error_message(int ernb)
{
	if (ernb == 1)
		write(1, "Error: argument", 15);
	if (ernb == 2)
		write(1, "Error: Operation file corrupted\n", 32);
	return (1);
}

int		clean(FILE *file, int errnb)
{
	file ? fclose(file) : 0;
	return (error_message(errnb));ß
}

int		draw_circle(t_data *d, int i, float x, float y)
{
	float dis;

	while (i >= 0)
	{
		dis = sqrtf(powf(x - d->x[i], 2.) + powf(y - d->y[i], 2.));
		if (dis <= d->radius[i])
		{
			if (d->fill[i] == 'C' || d->radius[i] - dis < 1.00000000)
			{
				write(1, &d->cc[i], 1);
				return (1);
			}
		}
		i--;
	}
	return (0);
}

void	draw(t_data *d)
{
	float x;
	float y;

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			if (draw_circle(d, d->i - 1, x, y))
			{
				x++;
				continue ;
			}
			else
			{
				write(1, &d->cs, 1);
				x++;
			}
		}
		write(1, "\n", 1);
		y++;
	}
}

int		main(int argc, char *argv[])
{
	int		ret;
	FILE	*file;
	t_data	d;

	d.i = 0;
	if (argc != 2)
		return (error_message(1));
	file = fopen(argv[1], "r");
	if (!file)
		return (error_message(2));
	ret = fscanf(file, "%d %d %c\n", &d.w, &d.h, &d.cs);
	if (ret != 3 || d.w < 1 || d.w > 300 || d.h < 1 || d.h > 300)
		return (clean(file, 2));
	while (1)
	{
		ret = fscanf(file, "%c %f %f %f %c\n", &d.fill[d.i], &d.x[d.i], &d.y[d.i], &d.radius[d.i], &d.cc[d.i]);
		if (ret == EOF)
			break ;
		if (ret != 5 || (d.fill[d.i] != 'c' && d.fill[d.i] != 'C') || d.radius[d.i] <= 0)
			return (clean(file, 2));
		d.i++;
	}
	draw(&d);
	fclose(file);
	return (0);
}
