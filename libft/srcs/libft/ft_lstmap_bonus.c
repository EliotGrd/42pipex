/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraud <egiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:08:59 by egiraud           #+#    #+#             */
/*   Updated: 2025/06/15 15:16:42 by egiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*next;
	void	*temp;

	if (!f || !del || !lst)
		return (NULL);
	head = NULL;
	while (lst)
	{
		temp = f(lst->content);
		next = ft_lstnew(temp);
		if (!next)
		{
			del(temp);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, next);
		lst = lst->next;
	}
	return (head);
}
