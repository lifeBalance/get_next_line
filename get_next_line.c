/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:34 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/23 23:06:44 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE];
	static size_t	rem = 0;
	size_t			bytes_read;

	bytes_read = read(fd, buf + rem, BUFF_SIZE - rem) + rem;
	if (bytes_read > 0 || rem)
	{
		build_line(fd, line, buf, &rem);
		return (1);
	}
	return (bytes_read);
}

void	build_line(int fd, char **line, char *buf, size_t *rem)
{
	t_list			*line_lst;
	size_t			ln_size;

	ln_size = 0;
	line_lst = NULL;
	while (!ft_strchr(buf, '\n') && !ft_strchr(buf, '\0'))
	{
		ft_lst_push_back(&line_lst,
			ft_lstnew(ft_strsub(buf, 0, BUFF_SIZE), BUFF_SIZE));
		ln_size += BUFF_SIZE;
		ft_bzero(buf, BUFF_SIZE);
		read(fd, buf, BUFF_SIZE);
	}
	if (ft_strchr(buf, '\n'))
		ln_size += ft_strchr(buf, '\n') - buf;
	else if (ft_strchr(buf, '\0'))
		ln_size += ft_strchr(buf, '\0') - buf;
	*line = ft_strnew(ln_size);
	while (line_lst)
	{
		ft_strcat(*line, line_lst->content);
		line_lst = line_lst->next;
	}
	ft_lstdel(&line_lst, free_willy);
	*rem = end_line(line, buf);
}

size_t	end_line(char **ln, char *buf)
{
	int		len_nl;
	int		len_null;

	len_nl = ft_strchr(buf, '\n') - buf;
	len_null = ft_strchr(buf, '\0') - buf;
	if (len_nl >= 0)
	{
		ft_memcpy(*ln + ft_strlen(*ln), buf, len_nl);
		ft_memmove(buf, buf + (len_nl + 1), BUFF_SIZE - (len_nl + 1));
		ft_bzero(buf + BUFF_SIZE - (len_nl + 1), len_nl + 1);
	}
	else if (len_null >= 0)
	{
		ft_memcpy(*ln + ft_strlen(*ln), buf, len_null);
		ft_bzero(buf, BUFF_SIZE);
	}
	return (ft_strlen(buf));
}

void	free_willy(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}
