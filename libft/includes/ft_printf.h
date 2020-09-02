/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:01:33 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/24 16:30:37 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "./libft.h"

typedef	struct	s_printf
{
	char		*format;
	va_list		va_lst;
	va_list		va;
	va_list		va_copy;
	int			return_value;
}				t_printf;

typedef	struct	s_option
{
	int			arg_length;
	char		conversion;
	int			flag_plus;
	int			flag_left;
	int			flag_space;
	int			flag_zero;
	int			flag_sharp;
	int			width;
	int			precision;
	int			mod_h;
	int			mod_maj_l;
	char		*f_str;
	int			f_sign;
}				t_option;

int				ft_printf(const char *format, ...);

/*
** printf_float.c
*/
char			*ull_itoa(unsigned long long n);
int				manage_float(t_printf *env, t_option *opt);
char			*free_str(char *str1, char *str2);

/*
** parse_option.c
*/

void			parse_opt(t_printf *env, t_option *opt);

/*
** print_conversions
*/

int				print_conversions(t_printf *env, t_option *opt);

/*
** print_d_i.c
*/
int				print_d_i(t_printf *env, t_option *opt);
char			*l_itoa(intmax_t n);

/*
** print_c_s_p.c
*/
void			print_char(t_printf *env, t_option *opt);
void			print_string(t_printf *env, t_option *opt);
int				print_p(t_printf *env, t_option *opt);

/*
** print_o_u_x_X.c
*/
int				print_oux(t_printf *env, t_option *opt);

/*
** tools.c
*/
char			*u_itoa(uintmax_t nb, char *base_char, int base);
int				padding(t_option *option, int len, char c);
void			putchar_len(char c, t_option *opt);
void			putstr_len(char *str, t_option *opt, int len);
int				count_digit(uintmax_t nb, unsigned int base);

/*
**print_percent.c
*/
int				print_percent(t_printf *env, t_option *opt);
char			*ftoa_bis(char *f_str, char *d_str, long double float_part);
#endif
