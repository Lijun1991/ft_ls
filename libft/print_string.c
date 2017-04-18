/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:52:04 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 19:52:08 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_len(char *s, int i, t_info *conver_info)
{
	while (i > 0 && i < (int)ft_strlen(s))
	{
		conver_info->count += pputchar(*s, conver_info->fd);
		i--;
		s++;
	}
}

void	print_reg_str_precision(t_info *conver_info, char *s, int i, int j)
{
	i = conver_info->field_width - ft_strlen(s);
	j = conver_info->field_width - conver_info->precision;
	if (conver_info->star == '*' && conver_info->precision == 0)
		conver_info->count += pputstr(s, conver_info->fd);
	if (conver_info->precision >= (int)ft_strlen(s))
	{
		if (conver_info->flag_info->minus == '-')
			put_str_helper(conver_info, i, s);
		else
		{
			print_space_helper(conver_info, i);
			conver_info->count += pputstr(s, conver_info->fd);
		}
	}
	else if (conver_info->flag_info->minus == '-')
	{
		ft_putstr_len(s, conver_info->precision, conver_info);
		print_nbr_helper(conver_info, j, ' ');
	}
	else
	{
		print_space_helper(conver_info, j);
		ft_putstr_len(s, conver_info->precision, conver_info);
	}
}

void	print_reg_string(t_info *conver_info, char *s, int i, int j)
{
	i = conver_info->field_width - ft_strlen(s);
	if (conver_info->precision == -1)
	{
		if (conver_info->flag_info->minus == '-')
		{
			if (conver_info->is_nopre == 0 && conver_info->is_dot == 1 && \
				conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
				print_nbr_helper(conver_info, conver_info->field_width, ' ');
			else
				put_str_helper(conver_info, i, s);
		}
		else
		{
			if (conver_info->is_nopre == 0 && conver_info->is_dot == 1 && \
				conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
				print_space_helper(conver_info, conver_info->field_width);
			else
			{
				print_space_helper(conver_info, i);
				conver_info->count += pputstr(s, conver_info->fd);
			}
		}
	}
	else
		print_reg_str_precision(conver_info, s, i, j);
}

void	print_null(t_info *conver_info)
{
	if (conver_info->field_width != -1)
	{
		if (conver_info->is_nopre == 1 && conver_info->is_dot == 1 && \
			conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
		{
			conver_info->count += pputstr("(null)", conver_info->fd);
			return ;
		}
		print_space_helper(conver_info, conver_info->field_width);
	}
	else
	{
		if (conver_info->is_nopre == 1 && conver_info->is_dot == 1 && \
			conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
		{
			conver_info->count += pputstr("(null)", conver_info->fd);
			return ;
		}
		if (conver_info->is_nopre == 0 && conver_info->is_dot == 1 && \
			conver_info->is_dot_zero == 0 && conver_info->is_dot_pre == 0)
		{
			conver_info->count += pputstr("(null)", conver_info->fd);
			return ;
		}
	}
}

void	print_string(t_info *conver_info, va_list args, int sign)
{
	char	*s;
	wchar_t	*ws;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strncmp(conver_info->len_mod, "l", 1) == 0)
	{
		ws = va_arg(args, wchar_t*);
		if (!ws)
		{
			conver_info->count += pputstr("(null)", conver_info->fd);
			return ;
		}
		print_wide_string(conver_info, ws, sign);
	}
	else
	{
		s = va_arg(args, char*);
		if (!s)
			print_null(conver_info);
		else
			print_reg_string(conver_info, s, i, j);
	}
}
