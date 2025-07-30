/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:42:12 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:16:13 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1tmp;
	unsigned char	*s2tmp;

	s1tmp = (unsigned char *) s1;
	s2tmp = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*s1tmp != *s2tmp)
			return (*s1tmp - *s2tmp);
		s1tmp++;
		s2tmp++;
	}
	return (0);
}
