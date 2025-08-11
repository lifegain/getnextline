/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktrzcins <ktrzcins@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:54:22 by ktrzcins          #+#    #+#             */
/*   Updated: 2025/08/11 14:54:24 by ktrzcins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*substr(char *str, int start, int len)
{
	char	*new_str;
	int		i;

	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	if (len == 0 || !str)
	{
		new_str[0] = '\0';
		return (new_str);
	}
	i = 0;
	while (i < len && str[start + i])
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	*read_until_newline(int fd, char *old_text)
{
	char	*buf;
	char	*new_text;
	int		bytes;

	if (!old_text)
		old_text = substr(NULL, 0, 0);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf || !old_text)
		return (free(old_text), free(buf), NULL);
	while (!ft_strchr(old_text, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		new_text = ft_strjoin(old_text, buf);
		if (!new_text)
			return (free(buf), free(old_text), NULL);
		free(old_text);
		old_text = new_text;
	}
	free(buf);
	if (bytes == -1)
		return (free(old_text), NULL);
	return (old_text);
}

static char	*extract_line(char *text)
{
	int		i;
	char	*line;

	if (!text || text[0] == '\0')
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\n')
		i++;
	line = substr(text, 0, i);
	return (line);
}

static char	*save_rest(char *text)
{
	char	*rest;
	int		i;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
		return (free(text), NULL);
	i++;
	if (!text[i])
		return (free(text), NULL);
	rest = substr(text, i, ft_strlen(text) - i);
	free(text);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_until_newline(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(saved);
	if (!line)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	saved = save_rest(saved);
	return (line);
}
