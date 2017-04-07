/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 21:28:55 by lwang             #+#    #+#             */
/*   Updated: 2016/10/20 14:51:43 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	int		i;
	int		j;
	char	*ps1;
	int		len;

	i = 0;
	j = 0;
	ps1 = (char*)s1;
	len = ft_strlen(s1);
	while (s2[j])
	{
		ps1[len + j] = s2[j];
		j++;
	}
	ps1[len + j] = '\0';
	return (ps1);
}
