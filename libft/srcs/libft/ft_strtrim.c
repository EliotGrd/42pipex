/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:30:39 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:14:32 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	compare(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*nstr;
	int		i;
	int		j;
	int		k;

	i = ft_strlen(s) - 1;
	j = 0;
	if (ft_strlen(s) == 0)
		return (ft_strdup(""));
	while (compare((char *)set, s[j]) == 1)
		j++;
	while (compare((char *)set, s[i]) == 1 && i > 0)
		i--;
	k = 0;
	if (i < j)
		return (ft_strdup(""));
	nstr = malloc(sizeof(char) * (i - j + 2));
	if (!nstr)
		return (NULL);
	while (j <= i)
		nstr[k++] = s[j++];
	nstr[k] = 0;
	return (nstr);
}
