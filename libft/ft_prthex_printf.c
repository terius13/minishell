/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prthex_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 22:44:58 by ting              #+#    #+#             */
/*   Updated: 2023/12/30 15:00:10 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_prthex_printf(unsigned long n, char format)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (format == 'X')
		base = "0123456789ABCDEF";
	else if (format == 'p')
	{
		if (n == 0)
			return (ft_prtstr_printf("(nil)"));
	}
	if (n > 15)
		count += ft_prthex_printf(n / 16, format);
	n = n % 16;
	if (count == 0 && format == 'p')
		count += ft_prtstr_printf("0x");
	count += ft_prtchar_printf(base[n]);
	return (count);
}
