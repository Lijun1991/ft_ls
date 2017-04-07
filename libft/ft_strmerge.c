/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 19:01:20 by lwang             #+#    #+#             */
/*   Updated: 2016/12/14 16:15:42 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strmerge(char *a, char *b)
{
	char *ret;

	ret = ft_strjoin(a, b);
	if (ft_strcmp(a, "") != 0)
	{
		free(a);
		a = NULL;
	}
	free(b);
	return (ret);
}
