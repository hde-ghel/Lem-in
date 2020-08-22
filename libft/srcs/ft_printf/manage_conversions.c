/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_conversions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:53:51 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/24 16:36:38 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int				print_conversions(t_printf *env, t_option *opt)
{
	opt->conversion = *env->format;
	if (opt->conversion == 'c')
		print_char(env, opt);
	else if (opt->conversion == 's')
		print_string(env, opt);
	else if (opt->conversion == 'p')
		return (print_p(env, opt));
	else if (opt->conversion == '%')
		print_percent(env, opt);
	else if (opt->conversion == 'd' || opt->conversion == 'i')
		return (print_d_i(env, opt));
	else if (opt->conversion == 'o' || opt->conversion == 'u'
			|| opt->conversion == 'x' || opt->conversion == 'X')
		return (print_oux(env, opt));
	else if (opt->conversion == 'f')
		return (manage_float(env, opt));
	else if (opt->width)
		padding(opt, opt->width - 1, opt->flag_zero ? '0' : ' ');
	return (0);
}

static	int		count_digit_ull(unsigned long long nb, unsigned int base)
{
	int		count;

	count = 1;
	while (nb >= base)
	{
		nb /= base;
		count++;
	}
	return (count);
}

char			*ull_itoa(unsigned long long n)
{
	int			len;
	char		*str;

	len = count_digit_ull(n, 10);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[0] = '0';
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char			*free_str(char *str1, char *str2)
{
	if (str1 != NULL)
		ft_strdel(&str1);
	if (str2 != NULL)
		ft_strdel(&str2);
	return (NULL);
}
