/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:52:55 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/24 18:52:56 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line_bonus.h"

/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start > slen || len == 0)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = 0;
	return (result);
}
*/

char	*ft_strchr_s(char *str, char c, int size)
{
	int	i;

	i = 0;
	while (str[i] && i < size)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (0);
}

/*
char	*ft_strdup(char *str)
{
	char	*nstr;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	nstr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!nstr)
		return (NULL);
	while (str[i])
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = 0;
	return (nstr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*nstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	nstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!nstr)
		return (NULL);
	while (s1[i])
	{
		nstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		nstr[i++] = s2[j++];
	nstr[i] = 0;
	return (nstr);
}
*/
