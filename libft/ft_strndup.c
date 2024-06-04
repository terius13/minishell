/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ting <ting@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:19:57 by ting              #+#    #+#             */
/*   Updated: 2024/05/30 14:28:21 by ting             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	len = n + 1;
	if (ft_strlen(s) < n)
		len = ft_strlen(s) + 1;
	new_str = malloc(len);
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, s, len - 1);
	new_str[len - 1] = '\0';
	return (new_str);
}
