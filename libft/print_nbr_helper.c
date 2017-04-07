/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 20:00:29 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 20:00:31 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	norm1_print_exit_precision(t_info *conver_info, \
	char *str, int len, int i)
{
	i = conver_info->field_width - len - conver_info->sign;
	if (conver_info->is_nopre == 0 && conver_info->is_dot == 0 \
		&& conver_info->is_dot_zero == 0 && \
		conver_info->is_dot_pre == 1)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) && \
			conver_info->flag_info->hash == '#')
			i--;
	}
	if (conver_info->star == '*' && conver_info->is_nopre == 0 && \
		conver_info->is_dot == 0 && conver_info->is_dot_zero == 1 \
		&& conver_info->is_dot_pre == 0)
	{
		if (conver_info->flag_info->zero == 'y')
			print_nbr_helper(conver_info, i, '0');
		else
			print_nbr_helper(conver_info, i, ' ');
	}
	else
		print_nbr_helper(conver_info, i, ' ');
	conver_info->count += pputstr(conver_info->pre_sign);
	print_str(str, conver_info);
}

static void	norm3_print_exit_precision(t_info *conver_info, \
	char *str, int len, int j)
{
	j = conver_info->precision - len;
	if (conver_info->is_nopre == 0 && conver_info->is_dot == 0 \
		&& conver_info->is_dot_zero == 0 \
		&& conver_info->is_dot_pre == 1)
	{
		if (ft_strchr("o", conver_info->conversion_specifier) &&\
			conver_info->flag_info->hash == '#')
			j--;
	}
	conver_info->count += pputstr(conver_info->pre_sign);
	print_nbr_helper(conver_info, j, '0');
	print_str(str, conver_info);
}

static void	norm2_print_exit_precision(t_info *conver_info, \
	char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (conver_info->precision + \
		conver_info->sign >= conver_info->field_width)
		norm3_print_exit_precision(conver_info, str, len, j);
	else
	{
		i = conver_info->field_width - \
		conver_info->precision - conver_info->sign;
		print_nbr_helper(conver_info, i, ' ');
		conver_info->count += pputstr(conver_info->pre_sign);
		j = conver_info->precision - len;
		print_nbr_helper(conver_info, j, '0');
		print_str(str, conver_info);
	}
}

void		print_exit_precision(t_info *conver_info, char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (conver_info->precision != -1)
	{
		if (len >= conver_info->precision)
		{
			if (conver_info->precision + \
				conver_info->sign >= conver_info->field_width)
			{
				conver_info->count += pputstr(conver_info->pre_sign);
				print_str(str, conver_info);
			}
			else
				norm1_print_exit_precision(conver_info, str, len, i);
		}
		else
			norm2_print_exit_precision(conver_info, str, len);
	}
}

void		print_no_precision_left(t_info *conver_info, char *str, int len)
{
	int		i;

	i = 0;
	if (conver_info->precision == -1)
	{
		if (len + conver_info->sign >= conver_info->field_width)
		{
			conver_info->count += pputstr(conver_info->pre_sign);
			print_str(str, conver_info);
		}
		else
		{
			i = conver_info->field_width - len - conver_info->sign;
			conver_info->count += pputstr(conver_info->pre_sign);
			print_str(str, conver_info);
			print_nbr_helper(conver_info, i, ' ');
		}
	}
}
