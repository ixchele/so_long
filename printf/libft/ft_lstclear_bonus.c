/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:41 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/14 12:22:46 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nex;

	if (!*lst || !del)
		return ;
	nex = (*lst)->next;
	while (*lst)
	{
		nex = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nex;
	}
}
