/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 16:59:46 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 14:58:45 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*t;
	size_t			i;

	t = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		t[i] = s[i];
		i++;
		if (s[i - 1] == (unsigned char)c)
		{
			return (dst + i);
		}
	}
	return (NULL);
}
