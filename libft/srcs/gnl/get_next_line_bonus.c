/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:05:39 by egiraud           #+#    #+#             */
/*   Updated: 2025/05/21 15:10:10 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line_bonus.h"

char	*fill_leftovers(char *stash)
{
	char	*tmp;
	int		i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	tmp = ft_strdup(stash + i + 1);
	free(stash);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*lining(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		line = ft_substr(stash, 0, i + 1);
	else
		line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_to(int fd, char *stash)
{
	int		bytes_read;
	char	*tmp;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr_s(stash, '\n', BUFFER_SIZE) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (NULL);
		free(stash);
		stash = tmp;
	}
	free (buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1024];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		return (stash[fd] = NULL, NULL);
	}
	if (!stash[fd])
	{
		stash[fd] = ft_strdup("");
		if (!stash[fd])
			return (NULL);
	}
	stash[fd] = read_to(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = lining(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		return (stash[fd] = NULL, NULL);
	}
	stash[fd] = fill_leftovers(stash[fd]);
	return (line);
}
