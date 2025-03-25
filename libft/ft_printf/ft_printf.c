/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:45:22 by afontan           #+#    #+#             */
/*   Updated: 2024/11/18 14:04:16 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_char(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		len += ft_ptrprintf(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		len += ft_unsigned_putnbr(va_arg(args, unsigned int));
	else if (c == 'x')
		len += ft_hexamin_putnbr(va_arg(args, unsigned int));
	else if (c == 'X')
		len += ft_hexamaj_putnbr(va_arg(args, unsigned int));
	else if (c == '%')
		len += ft_putchar('%');
	else if (c == ' ')
		len += printprc();
	else
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			len;
	const char	*str;

	va_start(args, format);
	str = format;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += check_char(str[i + 1], args);
			i += 2;
		}
		else
			len += ft_putchar((int)str[i++]);
	}
	va_end(args);
	return (len);
}
/* 
#include <stdio.h>

int main(void)
{
	char *str = NULL;

printf("nb de c : %d\n", ft_printf("Rslt de ma fonction : % //"));
printf("nb de c : %d\n", printf("Rslt de printf----- : % //"));
// printf("nb de c : %d\n", ft_printf("Rslt de ma fonction : %X //", -42));
// printf("nb de c : %d\n", printf("Rslt de printf----- : %X //", -42));
// printf("nb de c : %d\n", ft_printf("Rslt de ma fonction : %u //", 123456));
// printf("nb de c : %d\n", printf("Rslt de printf----- : %u //", 123456));
}   */