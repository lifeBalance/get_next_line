/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:34 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/21 23:28:14 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#define	B_SIZE 8 // DO NOTTT FORGET TO DELETE THIS SHYTE!

void	free_willy(void *content, size_t content_size);

int get_next_line(const int fd, char **line)
{
	static char	buffer[B_SIZE];
	//static char	buffer[BUFFER_SIZE];
	char		*nl;
	static size_t		bytes_read = 0;

	bytes_read = read(fd, buffer + bytes_read, B_SIZE - bytes_read);
	while (bytes_read > 0)
	{
		if ((nl = ft_strchr(buffer, '\n')))
		{
			*line = ft_strsub(buffer, 0, nl - buffer);
			ft_memmove(buffer, nl + 1, B_SIZE - (nl - buffer) - 1);
			ft_bzero(buffer + B_SIZE - (nl - buffer) - 1,
				(nl - buffer) + 1);
			// CHECK: Print the remaining content in the buffer
			ft_putstr("\nBytes read: ");
			ft_putnbr(bytes_read);
			ft_putstr(" Remains in buffer: ");
			ft_putendl(buffer);
			bytes_read = ft_strlen(buffer);
			break ;
		}
		else if (ft_strchr(buffer, '\0'))
			*line = ft_strsub(buffer, 0, ft_strlen(buffer));
		else
		{
			// Here we'll take care of lines that fill several buffers
			// We'll implement this part using linked-lists.
		}
		return (1);
	}
	// At this point, bytes_read is be 0 (end of file) or -1 (error)
	return (bytes_read);
}

void	free_willy(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}
