/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:17:35 by lwang             #+#    #+#             */
/*   Updated: 2017/04/06 20:17:40 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_nbr_helper(t_info *conver_info, int i, char c)
{
	while (i-- > 0)
		conver_info->count += pputchar(c);
}

void	write_helper(t_info *conver_info, char *str, int j)
{
	write(1, str, j);
	conver_info->count += j;
}

void	print_space_helper(t_info *conver_info, int i)
{
	while (i-- > 0)
	{
		if (conver_info->flag_info->zero == 'y')
			conver_info->count += pputchar('0');
		else
			conver_info->count += pputchar(' ');
	}
}

void	print_w_char_helper(t_info *conver_info, wchar_t *ws, int sign)
{
	while (*ws != '\0')
	{
		print_wide_char(conver_info, *ws, sign);
		ws++;
	}
}

void	put_str_helper(t_info *conver_info, int i, char *s)
{
	conver_info->count += pputstr(s);
	print_nbr_helper(conver_info, i, ' ');
}
