/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:38:32 by mugenan           #+#    #+#             */
/*   Updated: 2024/11/10 02:56:54 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	void	*tc;
	t_list	*final;

	if (!lst)
		return (NULL);
	final = NULL;
	while (lst != NULL)
	{
		tc = (*f)(lst->content);
		if (!tc)
			return (ft_lstclear(&final, del), NULL);
		tmp = ft_lstnew(tc);
		if (!tmp)
			return (del(tc), ft_lstclear(&final, del), NULL);
		ft_lstadd_back(&final, tmp);
		lst = lst->next;
	}
	return (final);
}
