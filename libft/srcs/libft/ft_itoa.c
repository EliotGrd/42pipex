/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:02:08 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:17:09 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	lencalc(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	long	nb;
	char	*result;

	nb = n;
	count = lencalc(nb);
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		result[0] = '-';
	}
	if (n == 0)
		result[0] = '0';
	result[count] = 0;
	while (nb != 0)
	{
		result[--count] = ((nb % 10) + 48);
		nb /= 10;
	}
	return (result);
}
