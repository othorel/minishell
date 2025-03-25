/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontan <afontan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:29:23 by afontan           #+#    #+#             */
/*   Updated: 2024/11/18 14:03:56 by afontan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int nb);
int		ft_unsigned_putnbr(unsigned int nb);
int		ft_hexamin_putnbr(unsigned int nb);
int		ft_hexamaj_putnbr(unsigned int nb);
int		ft_ptrprintf(void *ptr);
int		ft_long_putnbr(unsigned long nb);
int		particular_case(int nb);
int		printprc(void);

#endif
