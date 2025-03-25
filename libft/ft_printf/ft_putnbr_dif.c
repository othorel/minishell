/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_dif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:09:19 by afontan           #+#    #+#             */
/*   Updated: 2024/11/18 10:59:31 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	int	tmp;
	int	count;

	count = 0;
	tmp = nb;
	if (nb == 0 || nb == -2147483648)
	{
		count = particular_case(nb);
		return (count);
	}
	while (tmp != 0)
	{
		tmp = tmp / 10;
		count ++;
	}
	if (nb < 0)
	{
		write (1, "-", 1);
		nb = -nb;
		count ++;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
	return (count);
}

int	ft_unsigned_putnbr(unsigned int nb)
{
	unsigned long	tmp;
	int				count;

	count = 0;
	tmp = nb;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 10;
		count ++;
	}
	if (nb > 9)
		ft_unsigned_putnbr(nb / 10);
	ft_putchar(nb % 10 + 48);
	return (count);
}

int	ft_hexamin_putnbr(unsigned int nb)
{
	unsigned int	tmp;
	int				count;
	char			*base;

	base = "0123456789abcdef";
	count = 0;
	tmp = nb;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		count ++;
	}
	if (nb > 15)
		ft_hexamin_putnbr(nb / 16);
	ft_putchar(base[nb % 16]);
	return (count);
}

int	ft_hexamaj_putnbr(unsigned int nb)
{
	unsigned int	tmp;
	int				count;
	char			*base;

	base = "0123456789ABCDEF";
	count = 0;
	tmp = nb;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		count ++;
	}
	if (nb > 15)
		ft_hexamaj_putnbr(nb / 16);
	ft_putchar(base[nb % 16]);
	return (count);
}

int	ft_long_putnbr(unsigned long nb)
{
	unsigned long	tmp;
	int				count;
	char			*base;

	base = "0123456789abcdef";
	count = 0;
	tmp = nb;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		count ++;
	}
	if (nb > 15)
		ft_long_putnbr(nb / 16);
	ft_putchar(base[nb % 16]);
	return (count);
}
