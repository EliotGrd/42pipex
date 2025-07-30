/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:17:39 by egiraud           #+#    #+#             */
/*   Updated: 2025/05/12 01:25:48 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	check_cases(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_putchar_c(va_arg(args, int));
	else if (specifier == 's')
			count += ft_putstr_c(va_arg(args, char *));
	else if (specifier == 'p')
			count += ft_putaddress(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
			count += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
			count += ft_putunsigned_base(va_arg(args, unsigned int), \
								"0123456789");
	else if (specifier == 'x')
			count += ft_putunsigned_base(va_arg(args, unsigned int), \
								"0123456789abcdef");
	else if (specifier == 'X')
			count += ft_putunsigned_base(va_arg(args, unsigned int), \
								"0123456789ABCDEF");
	else
		count += ft_putchar_c('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			count += ft_putchar_c(str[i]);
			i++;
		}
		else
		{
			count += check_cases(str[i + 1], args);
			i += 2;
		}
	}
	va_end(args);
	return (count);
}
