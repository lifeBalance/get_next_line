/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:34 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/25 22:14:52 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **ln)
{
	static char		buf[BUFF_SIZE + 1] = {0};
	int				bytes_read;
	char			*tmp_ln;
	size_t			tmp_len;

	tmp_ln = NULL;
	tmp_len = 0;
	if (fd == 1 || fd == 2)
		return (-1);
	bytes_read = read(fd, buf + ft_strlen(buf), BUFF_SIZE - ft_strlen(buf));
	if (bytes_read < 0 || (bytes_read == 0 && ft_strlen(buf) == 0))
		return (bytes_read);
	if (ft_strlen(buf) == 8 && !ft_strchr(buf, '\n'))
		if (build_ln(fd, &tmp_ln, buf, &tmp_len) == -1)
			return (-1);
	if (end_ln(ln, tmp_ln, buf) == -1)
		return (-1);
	return (1);
}

int	build_ln(int fd, char **tmp_ln, char *buf, size_t *tmp_len)
{
	t_list	*ln_lst;

	ln_lst = NULL;
	if (build_lst(fd, buf, &ln_lst, tmp_len) == -1)
		return (-1);
	*tmp_ln = ft_strnew(*tmp_len);
	if (!(*tmp_ln))
		return (-1);
	while (ln_lst)
	{
		ft_strcat(*tmp_ln, ln_lst->content);
		ln_lst = ln_lst->next;
	}
	ft_lstdel(&ln_lst, free_willy);
	return (0);
}

int	build_lst(int fd, char *buf, t_list **ln_lst, size_t *tmp_len)
{
	t_list	*ln_node;

	while (ft_strlen(buf) == 8 && !ft_strchr(buf, '\n'))
	{
		ln_node = ft_lstnew(ft_strsub(buf, 0, BUFF_SIZE), BUFF_SIZE);
		if (!ln_node)
		{
			ft_lstdel(ln_lst, free_willy);
			return (-1);
		}
		*tmp_len += BUFF_SIZE;
		ft_lst_push_back(ln_lst, ln_node);
		ft_strclr(buf);
		read(fd, buf, BUFF_SIZE);
	}
	return (0);
}

int	end_ln(char **ln, char *tmp_ln, char *buf)
{
	size_t	ending_len;
	size_t	tmp_len;

	ending_len = 0;
	if (ft_strchr(buf, '\n'))
		ending_len = ft_strchr(buf, '\n') - buf;
	else if (ft_strchr(buf, '\0'))
		ending_len = ft_strlen(buf);
	tmp_len = 0;
	if (tmp_ln)
		tmp_len += ft_strlen(tmp_ln);
	*ln = ft_strnew(tmp_len + ending_len);
	if (!(*ln))
		return (-1);
	if (tmp_ln)
		ft_strcpy(*ln, tmp_ln);
	ft_memcpy(*ln + tmp_len, buf, ending_len);
	ft_strdel(&tmp_ln);
	ft_memmove(buf, buf + (ending_len + 1), BUFF_SIZE - (ending_len + 1));
	ft_strclr(buf + BUFF_SIZE - (ending_len + 1));
	return (0);
}

void	free_willy(void *content, size_t content_size)
{
	free(content);
	(void)content_size;
}
