/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 20:58:29 by egiraud           #+#    #+#             */
/*   Updated: 2025/07/31 20:59:28 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	char	*p;

	result = pmalloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	p = result;
	if (s1)
	{
		ft_memcpy(p, s1, ft_strlen(s1));
		p += ft_strlen(s1);
	}
	if (s2)
	{
		ft_memcpy(p, s2, ft_strlen(s2));
		p += ft_strlen(s2);
	}
	if (s3)
	{
		ft_memcpy(p, s3, ft_strlen(s3));
		p += ft_strlen(s3);
	}
	*p = 0;
	return result;
}
