/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 21:21:38 by lwang             #+#    #+#             */
/*   Updated: 2017/03/14 21:21:42 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	norm_print_sign(t_info *conver_info, int sign, char *pre_sign)
{
	if (ft_strchr("xX", conver_info->conversion_specifier) && \
		conver_info->flag_info->hash == '#')
	{
		if (conver_info->iszero == 1 && !(sign = 0))
			pre_sign = "\0\0";
		else
		{
			if (conver_info->conversion_specifier == 'x')
				pre_sign = "0x\0";
			else
				pre_sign = "0X\0";
			sign = 2;
		}
	}
	if (conver_info->conversion_specifier == 'x' && ft_strncmp(\
		conver_info->len_mod, "l", 1) == 0 && conver_info->isp == 1)
	{
		pre_sign = "0x\0";
		sign = 2;
	}
	ft_strcpy(conver_info->pre_sign, pre_sign);
	return (sign);
}

int			print_sign(t_info *conver_info, int sign)
{
	char	*pre_sign;

	pre_sign = "\0\0";
	if (sign == 1)
		pre_sign = "-\0";
	if (conver_info->flag_info->plus == '+' && sign != 1 && \
		conver_info->conversion_specifier == 'd' && (sign = 1))
		pre_sign = "+\0";
	if (conver_info->flag_info->space == ' ' && sign != 1 && \
		conver_info->conversion_specifier == 'd' && (sign = 1))
		pre_sign = " \0";
	if (conver_info->conversion_specifier == 'o' && \
		conver_info->flag_info->hash == '#')
	{
		sign = 1;
		if (conver_info->iszero == 1)
			sign = 0;
		pre_sign = "\0\0";
	}
	sign = norm_print_sign(conver_info, sign, pre_sign);
	return (sign);
}

char		*get_flag_info(t_info *conver_info, char *str)
{
	ft_bzero(conver_info->flag_info, sizeof(t_flag));
	while (*str == '#' || *str == '-' || *str == '+' \
		|| *str == ' ' || *str == '0')
	{
		if (*str == '#')
			conver_info->flag_info->hash = '#';
		else if (*str == '-')
			conver_info->flag_info->minus = '-';
		else if (*str == '+')
			conver_info->flag_info->plus = '+';
		else if (*str == ' ')
			conver_info->flag_info->space = ' ';
		else if (*str == '0')
			conver_info->flag_info->zero = 'y';
		else
			(ft_putstr("something wrong with flags"));
		str++;
	}
	return (str);
}

char		*print_convert_result(char *str, va_list args, t_info *conver_info)
{
	str = get_flag_info(conver_info, str);
	str = get_field_width(conver_info, str, args);
	str = get_precision(conver_info, str, args);
	str = get_length_modi(conver_info, str);
	if (ft_strchr("diouxXDOUpb", conver_info->conversion_specifier))
		print_number_conversion(conver_info, \
			conver_info->conversion_specifier, args);
	else if (ft_strchr("cCsS", conver_info->conversion_specifier))
		print_char_conversion(conver_info, \
			conver_info->conversion_specifier, args);
	else
		print_unvalid_conversion_specifier(conver_info, *str);
	str++;
	return (str);
}

int			ft_printf(char *format, ...)
{
	va_list	args;
	char	*str;
	t_info	conver_info;

	conver_info.flag_info = (t_flag*)malloc(sizeof(t_flag) * 1);
	conver_info.count = 0;
	va_start(args, format);
	str = (char*)format;
	while (*str != '\0')
	{
		while ((*str != '%') && (*str != '\0'))
		{
			conver_info.count += pputchar(*str);
			str++;
		}
		if (*str == '%')
			str++;
		if (*str != '\0')
			str = print_convert_result(str, args, &conver_info);
	}
	va_end(args);
	free(conver_info.flag_info);
	return (conver_info.count);
}
