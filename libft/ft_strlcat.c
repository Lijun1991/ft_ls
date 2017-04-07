/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 22:06:12 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 13:55:09 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t used;
	size_t length;
	size_t copy;

	used = ft_strlen((const char *)dst);
	length = ft_strlen(src);
	if (size <= used)
		return (length + size);
	if (size > 0 && used < size - 1)
	{
		copy = (length >= size - used) ? size - used - 1 : length;
		ft_memcpy(dst + used, src, copy);
		dst[used + copy] = '\0';
	}
	return (length + used);
}
