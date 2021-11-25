/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:56 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/24 23:22:54 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Macro Definitions.
*/
# define BUFF_SIZE 8

/*
** Nested Headers.
*/
# include "libft.h"

/*
** Function Prototypes.
*/
int		get_next_line(const int fd, char **line);
int		build_ln(int fd, char **tmp_ln, char *buf, size_t *ln_len);
int		build_lst(int fd, char *buf, t_list **ln_lst, size_t *tmp_len);
int		end_ln(char **ln, char *tmp_ln, char *buf, size_t *rem);
void	free_willy(void *content, size_t content_size);

#endif
