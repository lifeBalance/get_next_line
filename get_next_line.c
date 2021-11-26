/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:34 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/26 23:04:57 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	build_lst(int fd, char *buf, t_list **ln_lst, size_t *lst_len);
static int	build_ln(char **ln, char *buf, t_list **ln_lst, size_t lst_len);
static void	free_willy(void *content, size_t content_size);

int	get_next_line(const int fd, char **ln)
{
	static char	buf[BUFF_SIZE + 1] = {0};
	int			bytes_read;
	t_list		*ln_lst;
	size_t		lst_len;

	ln_lst = NULL;
	lst_len = 0;
	if (fd < 0 || fd == 1 || fd == 2 || !ln)
		return (-1);
	bytes_read = read(fd, buf + ft_strlen(buf), BUFF_SIZE - ft_strlen(buf));
	if (bytes_read < 0 || (bytes_read == 0 && ft_strlen(buf) == 0))
		return (bytes_read);
	if (build_lst(fd, buf, &ln_lst, &lst_len) < 0)
		return (-1);
	if (build_ln(ln, buf, &ln_lst, lst_len) < 0)
		return (-1);
	return (1);
}

static int	build_lst(int fd, char *buf, t_list **ln_lst, size_t *lst_len)
{
	t_list	*ln_node;
	size_t	bytes_read;

	while (ft_strlen(buf) == BUFF_SIZE && !ft_strchr(buf, '\n'))
	{
		*lst_len += BUFF_SIZE;
		ln_node = ft_lstnew(buf, BUFF_SIZE + 1);
		if (!ln_node)
		{
			ft_lstdel(ln_lst, free_willy);
			return (-1);
		}
		ft_lst_push_back(ln_lst, ln_node);
		ft_strclr(buf);
		bytes_read = read(fd, buf, BUFF_SIZE);
		if (bytes_read < 0)
		{
			ft_lstdel(ln_lst, free_willy);
			return (-1);
		}
	}
	if (*ln_lst && bytes_read == 0)
		ft_strclr(buf);
	return (bytes_read);
}

static int	build_ln(char **ln, char *buf, t_list **ln_lst, size_t lst_len)
{
	t_list	*tmp_lst;
	size_t	buf_len;

	buf_len = 0;
	if (ft_strchr(buf, '\n'))
		buf_len = ft_strchr(buf, '\n') - buf;
	else if (ft_strlen(buf) < BUFF_SIZE)
		buf_len = ft_strlen(buf);
	*ln = ft_strnew(lst_len + buf_len);
	if (!(*ln))
		return (-1);
	tmp_lst = *ln_lst;
	while (tmp_lst)
	{
		ft_strcat(*ln, tmp_lst->content);
		tmp_lst = tmp_lst->next;
	}
	if (*ln_lst)
		ft_lstdel(ln_lst, free_willy);
	ft_strncat(*ln, buf, buf_len);
	ft_memmove(buf, buf + (buf_len + 1), BUFF_SIZE - (buf_len + 1));
	ft_strclr(buf + BUFF_SIZE - (buf_len + 1));
	return (0);
}

static void	free_willy(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}

/*
**	#include <stdio.h>// <---DELETE!!!
**	printf("(get_next_line) buffer: |%s|\n", buf);// <---DELETE!!!
**	printf("(get_next_line) buffer: |%s|\n", buf);// <---DELETE!!!
**	printf("(build_ln) buffer: |%s|\n", buf);// <---DELETE!!!
**	printf("list before freeing: %p\n", *ln_lst);
**	printf("list was freed: %p\n", *ln_lst);
*/