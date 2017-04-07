/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wstr_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:57:30 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 19:57:32 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_wstrlen(wchar_t *tmp)
{
	int		len;

	len = 0;
	while (*tmp != '\0')
	{
		if (*tmp <= 0x7F)
			len += 1;
		else if (*tmp <= 0x7FF)
			len += 2;
		else if (*tmp <= 0xFFFF)
			len += 3;
		else if (*tmp <= 0x10FFFF)
			len += 4;
		tmp++;
	}
	return (len);
}

static void	norm1_fpl(char *str, wchar_t *ws, t_info *conver_info, int sign)
{
	str[0] = (((*ws & 0x07c0) >> 6) + 0xc0);
	str[1] = ((*ws & 0x03F0) + 0x80);
	print_wchar(conver_info, str, 2, sign);
}

static void	norm2_fpl(char *str, wchar_t *ws, t_info *conver_info, int sign)
{
	str[0] = (((*ws & 0xF000) >> 12) + 0xE0);
	str[1] = (((*ws & 0x0Fc0) >> 6) + 0x80);
	str[2] = ((*ws & 0x003F) + 0x80);
	print_wchar(conver_info, str, 3, sign);
}

static void	norm3_fpl(char *str, wchar_t *ws, t_info *conver_info, int sign)
{
	str[0] = (((*ws & 0x1c0000) >> 18) + 0xF0);
	str[1] = (((*ws & 0x03F000) >> 12) + 0x80);
	str[2] = (((*ws & 0x0Fc0) >> 6) + 0x80);
	str[3] = ((*ws & 0x003F) + 0x80);
	print_wchar(conver_info, str, 4, sign);
}

void		ft_putwstr_len(wchar_t *ws, t_info *conver_info, \
	int precision, int sign)
{
	char	str[4];

	while (*ws++ != '\0')
		if (ws[-1] <= 0x7F && precision >= 1)
		{
			print_regular_char(conver_info, ws[-1], sign);
			precision -= 1;
		}
		else if (ws[-1] <= 0x7FF && precision >= 2)
		{
			norm1_fpl(str, &ws[-1], conver_info, sign);
			precision -= 2;
		}
		else if (ws[-1] <= 0xFFFF && precision >= 3)
		{
			norm2_fpl(str, &ws[-1], conver_info, sign);
			precision -= 3;
		}
		else if (ws[-1] <= 0x10FFFF && precision >= 4)
		{
			norm3_fpl(str, &ws[-1], conver_info, sign);
			precision -= 4;
		}
		else
			break ;
}
