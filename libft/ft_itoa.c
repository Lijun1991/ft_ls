/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 21:49:06 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 15:14:57 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		n_len(int n)
{
	int		i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*dst;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = (n > 0) ? 0 : 1;
	if (n < 0 && n > -2147483647)
		n = -n;
	if (n == -0 || n == 0)
		return (ft_strdup("0"));
	len = n_len(n);
	dst = (char *)malloc((sizeof(char)) * (len + 1 + sign));
	if (!dst)
		return (NULL);
	dst[len + sign] = '\0';
	while (len + sign > 0)
	{
		dst[len + sign - 1] = (n % 10 + '0');
		n = n / 10;
		len--;
	}
	if (sign == 1)
		dst[0] = '-';
	return (dst);
}
