/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:23:19 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:13:19 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	print_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		print_fd('-', fd);
		n = -n;
	}
	if (n < 10)
	{
		print_fd(n + '0', fd);
	}
	else
	{
		ft_putnbr_fd((n / 10), fd);
		print_fd(n % 10 + '0', fd);
	}
}
