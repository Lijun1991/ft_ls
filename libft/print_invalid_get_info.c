/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_invalid_get_info.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 20:14:17 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 20:14:22 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_pre(wchar_t *ws, int precision)
{
	wchar_t *tmp;

	tmp = ws;
	while (*tmp != '\0')
	{
		if (*tmp <= 0x7F && precision >= 1)
			precision -= 1;
		else if (*tmp <= 0x7FF && precision >= 2)
			precision -= 2;
		else if (*tmp <= 0xFFFF && precision >= 3)
			precision -= 3;
		else if (*tmp <= 0x10FFFF && precision >= 4)
			precision -= 4;
		else
			break ;
		tmp++;
	}
	return (precision);
}

void	print_unvalid_conversion_specifier(t_info *conver_info, char s)
{
	int		i;

	i = 0;
	if (conver_info->flag_info->minus == '-')
	{
		i = conver_info->field_width - 1;
		conver_info->count += pputchar(s);
		print_nbr_helper(conver_info, i, ' ');
	}
	else
	{
		i = conver_info->field_width - 1;
		print_space_helper(conver_info, i);
		conver_info->count += pputchar(s);
	}
}
