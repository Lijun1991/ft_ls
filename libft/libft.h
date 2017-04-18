/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:34:36 by lwang             #+#    #+#             */
/*   Updated: 2017/04/05 21:07:31 by lwang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>
# include <stdarg.h>
# include <locale.h>
# include <wchar.h>

# define RED "\e[31;3m"
# define BLUE "\e[34;3m"
# define GREE "\e[32;3m"
# define YELLOW "\e[33;3m"
# define PURPLE "\e[35;3m"

# define CLN "\e[0m"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_string
{
	int		precision;
	int		is_char;
	char	chara;
	wchar_t	wchara;
}					t_string;

typedef struct		s_flag
{
	char	hash;
	char	minus;
	char	plus;
	char	space;
	char	zero;
}					t_flag;

typedef struct		s_info
{
	int		field_width;
	int		precision;
	char	conversion_specifier;
	t_flag	*flag_info;
	char	len_mod[3];
	char	pre_sign[3];
	int		count;
	int		iszero;
	int		is_nopre;
	int		is_dot;
	int		is_dot_zero;
	int		is_dot_pre;
	int		isp;
	int		sign;
	char	star;
	int		fd;
}					t_info;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *restrict s1, const char *restrict s2);
char				*ft_strncat(char *restrict s1, const char *restrict s2,
					size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
char				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char	const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list*lst, void(*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_strmerge(char *a, char *b);
int					ft_nbrlen(int nbr);

int					num_count(int n);
void				print_bits(unsigned char octet);
unsigned char		swap_bits(unsigned char octet);
int					word_count(char *str, char c);
int					skip_space(char const *str);

int					pputchar(char c, int fd);
int					pputstr(char const *s, int fd);
int					ft_abs(int n);

/*
** printf.c
*/
int					ft_printf(char *format, ...);
int					ft_fprintf(int fd, char *format, ...);
char				*print_convert_result(char *str, va_list args, \
	t_info *conver_info);
char				*get_flag_info(t_info *conver_info, char *str);
int					print_sign(t_info *conver_info, int sign);
/*
** printf_get_conversion_info.c
*/
char				*get_length_modi(t_info *conver_info, char *str);
char				*get_precision(t_info *conver_info, char *str, \
	va_list args);
char				*get_field_width(t_info *conver_info, char *str, \
	va_list args);
/*
** print_number_conversion.c
*/
void				get_less_conversion_specifier(char s, t_info *conver_info);
void				print_number_conversion(t_info *conver_info, \
	char c, va_list args);
void				print_result_capx(unsigned long long nbr, \
	t_info *conver_info, int base);
void				print_result(unsigned long long nbr, \
	t_info *conver_info, int base);
void				print_result_d(long long nbr, \
	t_info *conver_info, int base);
/*
** print_number.c
*/
long long			number_to_print_signed(t_info *conver_info, va_list args);
unsigned long long	number_to_print_unsigned(t_info *conver_info, va_list args);
void				print_nbr(t_info *conver_info, char *str, int len);
void				print_exit_precision_left(t_info *conver_info, \
	char *str, int len);
/*
** print_nbr_str.c
*/
void				print_no_precision(t_info *conver_info, char *str, int len);
void				print_str(char *str, t_info *conver_info);
/*
** print_nbr_helper.c
*/
void				print_no_precision_left(t_info *conver_info, \
	char *str, int len);
void				print_exit_precision(t_info *conver_info, \
	char *str, int len);
/*
** print_char_conversion.c
*/
void				print_char_conversion(t_info *conver_info, \
	char c, va_list args);
void				print_char(t_info *conver_info, va_list args, int sign);
void				print_regular_char(t_info *conver_info, \
	char chara, int sign);
void				print_wide_char(t_info *conver_info, \
	wchar_t wchara, int sign);
void				print_wchar(t_info *conver_info, char *str, \
	int j, int sign);
/*
** print_string.c
*/
void				print_string(t_info *conver_info, va_list args, int sign);
void				print_null(t_info *conver_info);
void				print_reg_string(t_info *conver_info, \
	char *s, int i, int j);
void				print_reg_str_precision(t_info *conver_info, \
	char *s, int i, int j);
void				ft_putstr_len(char *s, int i, t_info *conver_info);
/*
** print_wide_sting.c
*/
void				print_wide_string(t_info *conver_info, wchar_t *ws, \
	int sign);
void				print_w_str_precision(t_info *conver_info, \
	wchar_t *ws, int len, int sign);
/*
** print_wstr_helper.c
*/
void				ft_putwstr_len(wchar_t *ws, t_info *conver_info, \
	int precision, int sign);
int					ft_wstrlen(wchar_t *tmp);
/*
** printf_helper.c
*/
void				print_nbr_helper(t_info *conver_info, int i, char c);
void				write_helper(t_info *conver_info, char *str, int j);
void				print_space_helper(t_info *conver_info, int i);
void				print_w_char_helper(t_info *conver_info, \
	wchar_t *ws, int sign);
void				put_str_helper(t_info *conver_info, int i, char *s);
/*
** print_invalid_get_info.c
*/
void				print_unvalid_conversion_specifier(\
	t_info *conver_info, char s);
int					get_pre(wchar_t *ws, int precision);

#endif
