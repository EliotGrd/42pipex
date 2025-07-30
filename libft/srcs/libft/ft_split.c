/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:49:02 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:15:41 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			if (s[i] != c && ((i == 0) || s[i - 1] == c))
				count++;
		}
		i++;
	}
	return (count);
}

static void	*freeall(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	*splitter(char const *s, char c, int i)
{
	int		j;
	int		k;
	char	*nstr;

	j = 0;
	k = i;
	while (s[i] != c && s[i])
		i++;
	nstr = malloc(sizeof(char) * (i - k + 1));
	if (!nstr)
		return (NULL);
	while (s[k] != c && s[k])
		nstr[j++] = s[k++];
	nstr[j] = 0;
	return (nstr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		wd_count;
	char	**arr;

	i = 0;
	j = 0;
	wd_count = count_words(s, c);
	arr = malloc (sizeof(char *) * (wd_count + 1));
	if (!arr)
		return (NULL);
	while (j < wd_count)
	{
		while (s[i] && (s[i] == c))
			i++;
		arr[j] = splitter(s, c, i);
		if (!arr[j])
			return (freeall(arr, j));
		i += ft_strlen(arr[j]);
		j++;
	}
	arr[wd_count] = 0;
	return (arr);
}
