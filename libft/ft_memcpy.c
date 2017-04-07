/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:49:53 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 14:55:26 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*t;
	size_t			i;

	s = (unsigned char *)des;
	t = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s[i] = t[i];
		i++;
	}
	return (des);
}
