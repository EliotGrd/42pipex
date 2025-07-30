/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:14:13 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:16:06 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//difficulty is to understand that when dest ptr is after src one but in the ..
//.. src data you need to assign from end to start.

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_src;
	unsigned char	*tmp_dest;

	tmp_src = (unsigned char *) src;
	tmp_dest = (unsigned char *) dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (tmp_dest > tmp_src)
		while (n--)
			tmp_dest[n] = tmp_src[n];
	else
	{
		while (i < n)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (dest);
}
