/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_get_conversion_info.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 20:16:57 by lwang             #+#    #+#             */
/*   Updated: 2017/04/06 20:17:04 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*norm_glm(t_info *conver_info, char *str)
{
	if (ft_strncmp(str, "h", 1) == 0)
	{
		ft_strcpy(conver_info->len_mod, "h");
		str++;
	}
	if (ft_strncmp(str, "j", 1) == 0)
	{
		ft_strcpy(conver_info->len_mod, "j");
		str++;
	}
	if (ft_strncmp(str, "z", 1) == 0)
	{
		ft_strcpy(conver_info->len_mod, "z");
		str++;
	}
	if (ft_strncmp(str, "L", 1) == 0)
	{
		ft_strcpy(conver_info->len_mod, "L");
		str++;
	}
	return (str);
}

char			*get_length_modi(t_info *conver_info, char *str)
{
	ft_strcpy(conver_info->len_mod, "\0\0\0");
	if (ft_strncmp(str, "ll", 2) == 0)
	{
		ft_strcpy(conver_info->len_mod, "ll");
		str++;
		str++;
	}
	if (ft_strncmp(str, "hh", 2) == 0)
	{
		ft_strcpy(conver_info->len_mod, "hh");
		str++;
		str++;
	}
	if (ft_strncmp(str, "l", 1) == 0)
	{
		ft_strcpy(conver_info->len_mod, "l");
		str++;
	}
	str = norm_glm(conver_info, str);
	conver_info->conversion_specifier = *str;
	return (str);
}

static	char	*norm_gp_star(t_info *conver_info, char *str, va_list args)
{
	if (*str == '*')
	{
		conver_info->precision = va_arg(args, int);
		if (conver_info->precision < 0)
		{
			conver_info->star = '*';
			conver_info->precision = 0;
		}
		str++;
	}
	return (str);
}

char			*get_precision(t_info *conver_info, char *str, va_list args)
{
	conver_info->precision = -1;
	conver_info->is_nopre = 0;
	conver_info->is_dot = 0;
	conver_info->is_dot_zero = 0;
	conver_info->is_dot_pre = 0;
	if (*str != '.')
		conver_info->is_nopre = 1;
	if (*str == '.')
		str++;
	str = norm_gp_star(conver_info, str, args);
	if (*str >= '0' && *str <= '9')
		conver_info->precision = ft_atoi(str);
	if (!(*str >= '0' && *str <= '9') && conver_info->precision == -1)
		conver_info->is_dot = 1;
	if ((*str >= '0' && *str <= '9') || conver_info->precision != -1)
	{
		if (*str == '0' || conver_info->precision == 0)
			conver_info->is_dot_zero = 1;
		if ((*str >= '1' && *str <= '9') || \
			(conver_info->precision >= 1 && conver_info->precision <= 9))
			conver_info->is_dot_pre = 1;
	}
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}

char			*get_field_width(t_info *conver_info, char *str, va_list args)
{
	conver_info->field_width = -1;
	if (*str >= '1' && *str <= '9')
		conver_info->field_width = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str == '*')
	{
		conver_info->field_width = va_arg(args, int);
		if (conver_info->field_width < 0)
		{
			conver_info->field_width = -conver_info->field_width;
			conver_info->flag_info->minus = '-';
		}
		str++;
	}
	if (*str >= '1' && *str <= '9')
		conver_info->field_width = ft_atoi(str);
	while (*str >= '0' && *str <= '9')
		str++;
	return (str);
}
