/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mramadan <mramadan@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 15:28:38 by mramadan       #+#    #+#                */
/*   Updated: 2020/01/22 11:14:21 by mramadan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_list
{
	int			ret;
	int			prec;
	int			dot;
	int			width;
	int			neg;
	int			len;
	va_list		args;
}				t_struct;

int		ft_write(t_struct *f, char c)
{
	f->ret += write(1, &c, 1);
	return (1);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	write_str(char *str, t_struct *f)
{
	int i;

	i = 0;
	if (str == 0)
		str = "(null)";
	f->len = ft_strlen(str);
	if (f->dot && f->prec < f->len)
		f->len = f->prec;
	while (f->width > f->len)
		f->width -= ft_write(f, ' ');
	while (f->len > 0)
	{
		f->len -= ft_write(f, str[i]);
		i++;
	}
}

void	ft_putnbr(t_struct *f, long nb)
{
	if (nb > 9)
	{
		ft_putnbr(f, nb / 10);
		ft_putnbr(f, nb % 10);
	}
	else
		ft_write(f, nb + 48);
}

void	write_digit(long nb, t_struct *f)
{
	long nbc;

	if (nb < 0)
	{
		nb *= -1;
		f->neg = 1;
		f->width--;
	}
	nbc = nb;
	while (nbc > 0)
	{
		nbc /= 10;
		f->len++;
	}
	if (nb == 0)
		f->len = 1;
	if (f->dot && f->prec > f->len)
		f->width -= f->prec - f->len;
	while (f->width > f->len)
		f->width -= ft_write(f, ' ');
	if (f->neg && f->prec >= f->len)
		ft_write(f, '-');
	while (f->prec > f->len)
		f->prec -= ft_write(f, '0');
	if (f->neg && f->prec < f->len)
		ft_write(f, '-');
	if (f->dot && f->prec == 0 && nb == 0)
	{
		if (f->width > 0)
			ft_write(f, ' ');
		return ;
	}
	ft_putnbr(f, nb);
}

void	ft_puthex(t_struct *f, long n)
{
	int i;

	i = 0;
	if (n >= 16)
	{
		ft_puthex(f, n / 16);
		ft_puthex(f, n % 16);
	}
	else if (n > 9)
	{
		while (n > 9)
		{
			n--;
			i++;
		}
		ft_write(f, 96 + i);
	}
	else
		ft_write(f, 48 + n);
}

void	write_hex(long nb, t_struct *f)
{
	long nbc;

	nbc = nb;
	while (nbc > 0)
	{
		nbc /= 16;
		f->len++;
	}
	if (nb == 0)
		f->len = 1;
	if (f->dot && f->prec > f->len)
		f->width -= f->prec - f->len;
	while (f->width > f->len)
		f->width -= ft_write(f, ' ');
	if (f->neg && f->prec >= f->len)
		ft_write(f, '-');
	while (f->prec > f->len)
		f->prec -= ft_write(f, '0');
	if (f->neg && f->prec < f->len)
		ft_write(f, '-');
	if (f->dot && f->prec == 0 && nb == 0)
	{
		if (f->width > 0)
			ft_write(f, ' ');
		return ;
	}
	ft_puthex(f, nb);
}

void	find_flags(t_struct *f, const char **str)
{
	while (**str >= '0' && **str <= '9')
	{
		f->width = f->width * 10 + (**str - 48);
		(*str)++;
	}
	if (**str == '.')
	{
		f->dot = 1;
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			f->prec = f->prec * 10 + (**str - 48);
			(*str)++;
		}
	}
	if (**str == 's')
		write_str(va_arg(f->args, char *), f);
	if (**str == 'd')
		write_digit(va_arg(f->args, int), f);
	if (**str == 'x')
		write_hex(va_arg(f->args, unsigned int), f);
}

void	zero_flags(t_struct *f)
{
	f->dot = 0;
	f->prec = 0;
	f->width = 0;
	f->neg = 0;
	f->len = 0;
}

int		ft_printf(const char *str, ...)
{
	t_struct	f;

	f.ret = 0;
	va_start(f.args, str);
	while (*str)
	{
		while (*str != '%' && *str != '\0')
			str += ft_write(&f, *str);
		if (*str == '%')
		{
			str++;
			zero_flags(&f);
			find_flags(&f, &str);
		}
		if (*str == '\0')
			break ;
		str++;
	}
	va_end(f.args);
	return (f.ret);
}

int		main(void)
{
	int ft_ret;
	int pf_ret;

	ft_ret = ft_printf("%20.10x", -1234);
	printf("\nft_ret: %d", ft_ret);
	printf("\n");
	pf_ret = printf("%20.10x", -1234);
	printf("\npf_ret: %d", pf_ret);
	return (0);
}

void write_str(t_struct *f, char *str)
{
	int i;

	i = 0;
	if (!str)
		str = "(null)";
	f->len = ft_strlen(str);
	if (f->dot && f->prec < f->len)
		f->len = f->prec;
	while (f->width > f->len)
		f->width -= ft_write(f, ' ');
	while (f->len > 0)
	{
		f->len -= ft_write(f, *str);
		i++;
	}
}

void puthex(t_struct *f, long nb)
{
	int i;

	i = 0;
	if (nb >= 16)
	{
		puthex(f, nb / 16);
		puthex(f, nb % 16);
	}
	else if (nb > 9)
	{
		while (nb > 9)
		{
			nb--;
			i++;
		}
		ft_write(f, 96 + i);
	}
	else
		ft_write(f, nb + 48);
}	