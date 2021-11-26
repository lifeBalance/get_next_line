/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:56 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/26 19:48:39 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Macro Definitions.
*/
# define BUFF_SIZE 16

/*
** Nested Headers.
*/
# include "libft.h"

/*
** Function Prototypes.
*/
int		get_next_line(const int fd, char **line);
int		build_lst(int fd, char *buf, t_list **ln_lst, size_t *lst_len);
int		build_ln(char **ln, char *buf, t_list **ln_lst, size_t lst_len);
void	free_willy(void *content, size_t content_size);

#endif
