#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32

int	main()
{
	int fd;

	fd = open("txt.txt", O_RDONLY);
	if (fd < 0)
		return (-1);

	if (get_next_line(fd))
		return (1);
	else
		return (0);
}

char *get_next_line(int fd)
{
	static char *txt_buffer;
	char *txt_output;
	int numbytes;
	int c;

	
	c = 0;
	txt_buffer = malloc(sizeof(char) * (32 + 1));
	if (!the_text)
		return (NULL);
	numbytes = read(fd, txt_buffer, BUFFER_SIZE);
	if (numbytes == 0 || numbytes < 0)
		return (NULL);
	txt_buffer[numbytes] = '\0';
	txt_output = malloc(sizeof(char) * (numbytes + 1));
	if (!txt_output)
		return (NULL);
	while (txt_buffer[c] && c < numbytes)
	{
		txt_output[c] = txt_buffer[c];
		c++;
	}
	if (!ft_ischar(txt_output))
		get_next_line(fd);
	txt_output[c] = '\0';
	return (txt_output);
}

		




	

