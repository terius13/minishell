/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:08 by ting              #+#    #+#             */
/*   Updated: 2023/09/11 13:05:49 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/* 
int	main(void)
{
	printf("The char is 0, return: %d\n",ft_isdigit('0'));
	printf("The char is 4, return: %d\n",ft_isdigit('4'));
	printf("The char is A, return: %d\n",ft_isdigit('A'));
}
*/
