/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:12:00 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:16:17 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*stmp;
	unsigned char	ctmp;

	i = 0;
	stmp = (unsigned char *) s;
	ctmp = (unsigned char) c;
	while (i < n)
	{
		if (stmp[i] == ctmp)
			return ((void *)&stmp[i]);
		i++;
	}
	return (NULL);
}
