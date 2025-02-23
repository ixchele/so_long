/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:52:45 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/11 19:58:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *list)
{
	int		count;
	t_list	*lst;

	lst = list;
	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
