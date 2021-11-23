/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:34 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/23 12:43:35 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#define BUFFER_SIZE 8// DO NOTTT FORGET TO DELETE THIS SHYTE!

size_t	build_line(int fd, char **line, char *buf, size_t bytes_read);
void	end_line(char **ln, size_t ln_size, char *buf, size_t *rem);
void	free_willy(void *content, size_t content_size);
size_t	ft_bufchr(char *buf, char ch, size_t buf_size);

int	get_next_line(const int fd, char **line)
{
	static char		buf[BUFFER_SIZE];
	static size_t	rem = 0;
	size_t			bytes_read;
	size_t			ln_size;

	bytes_read = read(fd, buf + rem, BUFFER_SIZE - rem) + rem;
	rem = 0;
	if (!bytes_read && ft_strlen(buf))
		*line = ft_strsub(buf, 0, ft_strlen(buf));
	if (bytes_read > 0)
	{
		ln_size = build_line(fd, line, buf, bytes_read);
		end_line(line, ln_size, buf, &rem);
		return (1);
	}
	return (bytes_read);
}

size_t	build_line(int fd, char **line, char *buf, size_t bytes_read)
{
	t_list			*line_lst;
	size_t			ln_size;

	ln_size = 0;
	line_lst = NULL;
	while (bytes_read == 8 && !ft_bufchr(buf, '\n', BUFFER_SIZE))
	{
		ft_lst_push_back(&line_lst,
			ft_lstnew(ft_strsub(buf, 0, BUFFER_SIZE), BUFFER_SIZE));
		ln_size += bytes_read;
		ft_bzero(buf, BUFFER_SIZE);
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (ft_bufchr(buf, '\n', BUFFER_SIZE))
		ln_size += ft_bufchr(buf, '\n', BUFFER_SIZE);
	else if (ft_bufchr(buf, '\0', BUFFER_SIZE))
		ln_size += ft_bufchr(buf, '\0', BUFFER_SIZE);
	*line = ft_strnew(ln_size);
	while (line_lst)
	{
		ft_strcat(*line, line_lst->content);
		line_lst = line_lst->next;
	}
	ft_lstdel(&line_lst, free_willy);
	return (ln_size);
}

void	end_line(char **ln, size_t ln_size, char *buf, size_t *rem)
{
	size_t	len_nl;
	size_t	len_null;

	len_nl = ft_bufchr(buf, '\n', BUFFER_SIZE);
	len_null = ft_bufchr(buf, '\n', BUFFER_SIZE);
	if (len_nl)
	{
		ft_strlcat(*ln, buf, ln_size + 1);
		if (BUFFER_SIZE == len_nl + 1)
			ft_bzero(buf, BUFFER_SIZE);
		else
		{
			ft_memmove(buf, buf + len_nl + 1, BUFFER_SIZE - (len_nl + 1));
			ft_bzero(buf + BUFFER_SIZE - (len_nl + 1), len_nl + 1);
			*rem = ft_strlen(buf);
		}
	}
	else if (len_null)
	{
		ft_strlcat(*ln, buf, ln_size);
		ft_bzero(buf, BUFFER_SIZE);
	}
}

size_t	ft_bufchr(char *buf, char ch, size_t buf_size)
{
	size_t	len;

	len = 0;
	while (len < buf_size)
	{
		if (buf[len] == ch)
			return (len);
		len++;
	}
	return (0);
}

void	free_willy(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}
