/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktrzcins <ktrzcins@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:14:41 by ktrzcins          #+#    #+#             */
/*   Updated: 2025/07/01 13:46:36 by ktrzcins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_isnewline(const char *bufferchunk)
{
	int c;

	c = 0;
	while (bufferchunk[c] != '\n')
			c++;
	if (c == 32)
		return (0);
	else
		return (c);
}

int freestuff(char*)
{
	
