/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrodri <rodrodri@student.hive.fi >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 14:41:03 by rodrodri          #+#    #+#             */
/*   Updated: 2021/11/15 23:21:54 by rodrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*mapped_lst;
	t_list	*tmp_node;

	if (!lst || !f)
		return (NULL);
	mapped_lst = NULL;
	while (lst)
	{
		tmp_node = f(lst);
		if (!tmp_node)
			return (NULL);
		ft_lst_push_back(&mapped_lst, tmp_node);
		lst = lst->next;
	}
	return (mapped_lst);
}
