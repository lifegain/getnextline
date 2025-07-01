/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testprogram.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktrzcins <ktrzcins@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:45 by ktrzcins          #+#    #+#             */
/*   Updated: 2025/07/01 14:33:51 by ktrzcins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int linelength;
	char *trimmedbuffer;

	
	linelength = 0;
	c = 0;
	txt_buffer = malloc(sizeof(char) * (32 + 1));
	if (!txt_buffer)
		return (NULL);
	numbytes = read(fd, txt_buffer, BUFFER_SIZE);
	if (numbytes == 0 || numbytes < 0)
		return (NULL);
	txt_buffer[numbytes] = '\0';
	while (txt_buffer[c] != '\n' && c < numbytes)
		c++;
	if (c < BUFFER_SIZE && ft_isnewline(txt_buffer))
	{
		c = ft_isnewline(txt_buffer) + 1;
		txt_output = malloc(sizeof(char) * c + 1);
		if (!txt_output)
			return (NULL);
		while (linelength < c)
		{
			txt_output[linelength] = txt_buffer[linelength];
			linelength++;
		}
		//trim txt_buffer here
	}
	else if (!ft_isnewline(txt_buffer))
	{
		txt_output = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!txt_output)
			return(NULL);
		while (linelength < BUFFER_SIZE)
		{
			txt_output[linelength] = txt_buffer[linelength];
			linelength++;
		}
		//trim txt_buffer here
	}
