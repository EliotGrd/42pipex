/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:50:28 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 20:12:13 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static double	transfo(const char *nptr, int i, double nb)
{
	double	fraction;

	fraction = 0.1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	if (nptr[i] == '.')
	{
		i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			nb += (nptr[i++] - '0') * fraction;
			fraction *= 0.1;
		}
	}
	return (nb);
}

double	ft_atof(const char *nptr)
{
	int		i;
	int		sign;
	double	nb;

	i = 0;
	sign = 1;
	nb = 0.0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i + 1] < 48 || nptr[i + 1] > 57)
			return (nb);
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	nb = transfo(nptr, i, nb);
	return (nb * sign);
}
