/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number_conversion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 19:51:44 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 19:51:51 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		print_result(unsigned long long nbr, t_info *conver_info, int base)
{
	int					i;
	char				str[50];
	int					len;
	const char			tab[] = "0123456789abcdef";

	i = 49;
	conver_info->sign = 0;
	conver_info->iszero = 0;
	if (nbr == 0)
		conver_info->iszero = 1;
	conver_info->sign = print_sign(conver_info, conver_info->sign);
	str[49] = '\0';
	while (nbr >= 1)
	{
		str[--i] = (tab[nbr % base]);
		nbr /= base;
	}
	len = 49 - i;
	if (conver_info->iszero == 1)
		len = 1;
	while (i >= 0)
		str[--i] = '*';
	print_nbr(conver_info, str, len);
}

void		print_result_d(long long nbr, t_info *conver_info, int base)
{
	int					i;
	char				str[50];
	int					len;
	const char			tab[] = "0123456789abcdef";

	i = 49;
	conver_info->sign = 0;
	conver_info->iszero = 0;
	if (nbr < 0)
		conver_info->sign = 1;
	if (nbr == 0)
		conver_info->iszero = 1;
	conver_info->sign = print_sign(conver_info, conver_info->sign);
	str[49] = '\0';
	while (nbr)
	{
		str[--i] = (tab[ft_abs(nbr % base)]);
		nbr /= base;
	}
	len = 49 - i;
	if (conver_info->iszero == 1)
		len = 1;
	while (i >= 0)
		str[--i] = '*';
	print_nbr(conver_info, str, len);
}

void		print_result_capx(unsigned long long nbr, \
	t_info *conver_info, int base)
{
	int					i;
	char				str[50];
	int					len;
	const char			tab[] = "0123456789ABCDEF";

	i = 49;
	conver_info->sign = 0;
	conver_info->iszero = 0;
	if (nbr == 0)
		conver_info->iszero = 1;
	conver_info->sign = print_sign(conver_info, conver_info->sign);
	str[49] = '\0';
	while (nbr >= 1)
	{
		str[--i] = (tab[nbr % base]);
		nbr /= base;
	}
	len = 49 - i;
	if (conver_info->iszero == 1)
		len = 1;
	while (i >= 0)
		str[--i] = '*';
	print_nbr(conver_info, str, len);
}

void		get_less_conversion_specifier(char s, t_info *conver_info)
{
	conver_info->isp = 0;
	if (s == 'i')
		conver_info->conversion_specifier = 'd';
	if (s == 'p')
	{
		conver_info->isp = 1;
		conver_info->flag_info->hash = '#';
		ft_strcpy(conver_info->len_mod, "l");
		conver_info->conversion_specifier = 'x';
	}
	if (s == 'D')
	{
		ft_strcpy(conver_info->len_mod, "l");
		conver_info->conversion_specifier = 'd';
	}
	if (s == 'O')
	{
		ft_strcpy(conver_info->len_mod, "l");
		conver_info->conversion_specifier = 'o';
	}
	if (s == 'U')
	{
		ft_strcpy(conver_info->len_mod, "l");
		conver_info->conversion_specifier = 'u';
	}
}

void		print_number_conversion(t_info *conver_info, char c, va_list args)
{
	unsigned long long	nbr1;
	long long			nbr2;

	get_less_conversion_specifier(c, conver_info);
	if (conver_info->conversion_specifier == 'd')
		nbr2 = number_to_print_signed(conver_info, args);
	else
		nbr1 = number_to_print_unsigned(conver_info, args);
	if (conver_info->conversion_specifier == 'd')
		print_result_d(nbr2, conver_info, 10);
	else if (conver_info->conversion_specifier == 'u')
		print_result(nbr1, conver_info, 10);
	else if (conver_info->conversion_specifier == 'o')
		print_result(nbr1, conver_info, 8);
	else if (conver_info->conversion_specifier == 'x')
		print_result(nbr1, conver_info, 16);
	else if (conver_info->conversion_specifier == 'X')
		print_result_capx(nbr1, conver_info, 16);
	else if (conver_info->conversion_specifier == 'b')
		print_result_capx(nbr1, conver_info, 2);
}
