/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wide_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:54:06 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 19:54:08 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	norm1_pwsp(t_info *conver_info, wchar_t *ws, int len, int sign)
{
	int		i;

	i = conver_info->field_width - (len - get_pre(ws, \
		conver_info->precision));
	if (conver_info->flag_info->minus == '-')
	{
		print_w_char_helper(conver_info, ws, sign);
		print_nbr_helper(conver_info, i, ' ');
	}
	else
	{
		print_space_helper(conver_info, i);
		print_w_char_helper(conver_info, ws, sign);
	}
}

void		print_w_str_precision(t_info *conver_info, \
	wchar_t *ws, int len, int sign)
{
	int		i;

	i = 0;
	if (conver_info->precision >= len)
		norm1_pwsp(conver_info, ws, len, sign);
	else
	{
		i = conver_info->field_width - (conver_info->precision - \
			get_pre(ws, conver_info->precision));
		if (conver_info->flag_info->minus == '-')
		{
			ft_putwstr_len(ws, conver_info, conver_info->precision, sign);
			print_nbr_helper(conver_info, i, ' ');
		}
		else
		{
			print_space_helper(conver_info, i);
			ft_putwstr_len(ws, conver_info, conver_info->precision, sign);
		}
	}
}

static void	norm1_pws_left(t_info *conver_info, wchar_t *ws, int sign, int i)
{
	int		j;

	j = 0;
	if (conver_info->is_nopre == 0 && conver_info->is_dot == 1 && \
		conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
	{
		j = conver_info->field_width;
		print_nbr_helper(conver_info, j, ' ');
	}
	else
	{
		print_w_char_helper(conver_info, ws, sign);
		print_nbr_helper(conver_info, i, ' ');
	}
}

static void	norm2_pws(t_info *conver_info, wchar_t *ws, int sign, int i)
{
	int		j;

	j = 0;
	if (conver_info->is_nopre == 0 && conver_info->is_dot == 1 && \
		conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
	{
		j = conver_info->field_width;
		print_space_helper(conver_info, j);
	}
	else
	{
		print_space_helper(conver_info, i);
		print_w_char_helper(conver_info, ws, sign);
	}
}

void		print_wide_string(t_info *conver_info, wchar_t *ws, int sign)
{
	wchar_t	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = ws;
	len = ft_wstrlen(tmp);
	if (conver_info->field_width - len > 0)
		i = conver_info->field_width - len;
	if (conver_info->precision == -1)
	{
		if (conver_info->flag_info->minus == '-')
			norm1_pws_left(conver_info, ws, sign, i);
		else
			norm2_pws(conver_info, ws, sign, i);
	}
	else
		print_w_str_precision(conver_info, ws, len, sign);
}
