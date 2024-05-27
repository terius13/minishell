/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:23:51 by ting              #+#    #+#             */
/*   Updated: 2024/05/27 16:23:05 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*head;

	while (*lst)
	{
		head = (**lst).next;
		del((**lst).content);
		free(*lst);
		*lst = head;
	}
	*lst = NULL;
}
