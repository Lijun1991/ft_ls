/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:51:19 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 19:51:24 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	number_to_print_unsigned(t_info *conver_info, va_list args)
{
	if (ft_strlen(conver_info->len_mod) != 0)
	{
		if (ft_strncmp(conver_info->len_mod, "hh", 2) == 0)
			return ((unsigned char)va_arg(args, unsigned int));
		if (ft_strncmp(conver_info->len_mod, "h", 1) == 0)
			return ((unsigned short)va_arg(args, unsigned int));
		if (ft_strncmp(conver_info->len_mod, "l", 1) == 0)
			return (va_arg(args, unsigned long));
		if (ft_strncmp(conver_info->len_mod, "ll", 2) == 0)
			return (va_arg(args, unsigned long long));
		if (ft_strncmp(conver_info->len_mod, "j", 1) == 0)
			return (va_arg(args, uintmax_t));
		if (ft_strncmp(conver_info->len_mod, "z", 1) == 0)
		{
			return (size_t)(va_arg(args, unsigned long long));
		}
	}
	return (va_arg(args, unsigned int));
}

long long			number_to_print_signed(t_info *conver_info, va_list args)
{
	if (ft_strlen(conver_info->len_mod) != 0)
	{
		if (ft_strncmp(conver_info->len_mod, "hh", 2) == 0)
			return ((char)va_arg(args, int));
		if (ft_strncmp(conver_info->len_mod, "h", 1) == 0)
			return ((short)va_arg(args, int));
		if (ft_strncmp(conver_info->len_mod, "l", 1) == 0)
			return (va_arg(args, long int));
		if (ft_strncmp(conver_info->len_mod, "ll", 2) == 0)
			return (va_arg(args, long long int));
		if (ft_strncmp(conver_info->len_mod, "j", 1) == 0)
			return (va_arg(args, intmax_t));
		if (ft_strncmp(conver_info->len_mod, "z", 1) == 0)
			return (ssize_t)(va_arg(args, long long));
	}
	return (va_arg(args, int));
}

static void			norm_p_pre_left(t_info *conver_info, \
	char *str, int len, int i)
{
	int				j;

	j = 0;
	if (conver_info->precision + conver_info->sign >= conver_info->field_width)
	{
		j = conver_info->precision - len;
		conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
		print_nbr_helper(conver_info, j, '0');
		print_str(str, conver_info);
	}
	else
	{
		j = conver_info->precision - len;
		conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
		print_nbr_helper(conver_info, j, '0');
		print_str(str, conver_info);
		i = conver_info->field_width - conver_info->precision\
		- conver_info->sign;
		print_nbr_helper(conver_info, i, ' ');
	}
}

void				print_exit_precision_left(t_info *conver_info,\
	char *str, int len)
{
	int				i;

	i = 0;
	if (conver_info->precision != -1)
	{
		if (len >= conver_info->precision)
		{
			if (conver_info->precision + conver_info->sign\
			>= conver_info->field_width)
			{
				conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
				print_str(str, conver_info);
			}
			else
			{
				i = conver_info->field_width - len - conver_info->sign;
				conver_info->count += pputstr(conver_info->pre_sign, conver_info->fd);
				print_str(str, conver_info);
				print_nbr_helper(conver_info, i, ' ');
			}
		}
		else
			norm_p_pre_left(conver_info, str, len, i);
	}
}

void				print_nbr(t_info *conver_info, char *str, int len)
{
	if (conver_info->flag_info->minus != '-')
	{
		print_no_precision(conver_info, str, len);
		print_exit_precision(conver_info, str, len);
	}
	else
	{
		print_no_precision_left(conver_info, str, len);
		print_exit_precision_left(conver_info, str, len);
	}
}

