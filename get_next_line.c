#include "get_next_line.h"

static char	*substr(char *str, int start, int len)
{
	char *new_str;
	int i;

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

static char	*extract_line(char *text)
{
	int i;
	char *line;

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
	char *rest;
	int i;

	if (!text)
		return (NULL);
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

static char	*read_buffer(int fd, char *old_text)
{
	char *buf;
	int bytes;
	char *new_text;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes < 0)
	{
		free(buf);
		return (NULL);
	}
	if (bytes == 0)
	{
		free(buf);
		return (old_text);
	}
	buf[bytes] = '\0';
	new_text = ft_strjoin(old_text, buf);
	if (!new_text)
	{
		free(buf);
		return (NULL);
	}
	free(old_text);
	free(buf);
	return (new_text);
}

char	*get_next_line(int fd)
{
	static char *saved;
	char *line;
	char *new_text;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(saved), saved = NULL, NULL);
	if (!saved)
		saved = substr(NULL, 0, 0);
	if (!saved)
		return (NULL);
	while (!ft_strchr(saved, '\n'))
	{
		new_text = read_buffer(fd, saved);
		if (!new_text)
			return (free(saved), saved = NULL, NULL);
		if (new_text == saved)
			break ;
		saved = new_text;
	}
	line = extract_line(saved);
	if (!line)
		return (free(saved), saved = NULL, NULL);
	saved = save_rest(saved);
	return (line);
}
