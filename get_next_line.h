/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:56 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/23 22:44:53 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Macro Definitions.
*/
# define BUFF_SIZE 32

/*
** Function Prototypes.
*/
int		get_next_line(const int fd, char **line);
void	build_line(int fd, char **line, char *buf, size_t *rem);
size_t	end_line(char **ln, char *buf);
void	free_willy(void *content, size_t content_size);

#endif
