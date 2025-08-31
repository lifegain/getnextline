/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktrzcins <ktrzcins@student.42vienna.c>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:54:22 by ktrzcins          #+#    #+#             */
/*   Updated: 2025/08/31 14:00:00 by ktrzcins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *old)
{
	char	*buf;
	int		n;
	char	*joined;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buf);
		if (n < 0)
			return (NULL);
		return (old);
	}
	buf[n] = '\0';
	joined = ft_strjoin(old, buf);
	free(buf);
	if (!joined)
		return (NULL);
	free(old);
	return (joined);
}

static int	fill_buffer(int fd, char **psaved)
{
	char	*tmp;

	if (!*psaved)
	{
		*psaved = (char *)ft_calloc(1, 1);
		if (!*psaved)
			return (0);
	}
	while (!ft_strchr(*psaved, '\n'))
	{
		tmp = read_and_join(fd, *psaved);
		if (!tmp)
			return (0);
		if (tmp == *psaved)
			break ;
		*psaved = tmp;
	}
	return (1);
}

static char	*cut_out_line(char *s)
{
	int		i;
	int		j;
	char	*line;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = s[j];
	line[i] = '\0';
	return (line);
}

char	*save_rest(char *s)
{
	int		i;
	char	*rest;
	int		len;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	i++;
	len = ft_strlen(s + i);
	rest = (char *)malloc(len + 1);
	if (!rest)
		return (NULL);
	len = 0;
	while (s[i])
		rest[len++] = s[i++];
	rest[len] = '\0';
	free(s);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!fill_buffer(fd, &saved))
		return (NULL);
	line = cut_out_line(saved);
	saved = save_rest(saved);
	return (line);
}
