/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 23:00:56 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/26 23:05:39 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Macro Definitions.
*/
# define BUFF_SIZE 10000

/*
** Nested Headers.
*/
# include "libft.h"

/*
** Function Prototypes.
*/
int		get_next_line(const int fd, char **line);

#endif
