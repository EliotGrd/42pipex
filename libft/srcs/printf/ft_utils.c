/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:00:32 by egiraud           #+#    #+#             */
/*   Updated: 2025/05/12 01:25:42 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}*/

int	ft_putchar_c(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_c(char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		count += ft_putchar_c(*str);
		str++;
	}
	return (count);
}

static int	get_hexa(unsigned long nb)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (nb < 16)
	{
		count += ft_putchar_c(base[nb]);
	}
	if (nb >= 16)
	{
		count += get_hexa(nb / 16);
		count += get_hexa(nb % 16);
	}
	return (count);
}

int	ft_putaddress(void *ptr)
{
	int				count;
	unsigned long	nb;

	nb = (unsigned long)ptr;
	count = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += get_hexa(nb);
	return (count);
}
