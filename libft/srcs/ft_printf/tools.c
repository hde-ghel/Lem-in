/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:41:45 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/22 18:17:57 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		putstr_len(char *str, t_option *opt, int len)
{
	if (!str)
		return ;
	len = (!len ? ft_strlen(str) : (size_t)len);
	write(1, str, len);
	opt->arg_length += len;
}

int			padding(t_option *opt, int len, char c)
{
	int		i;

	i = 0;
	if (len <= 0)
		return (0);
	while (i < len)
	{
		write(1, &c, 1);
		i++;
	}
	opt->arg_length += len;
	return (0);
}

void		putchar_len(char c, t_option *opt)
{
	write(1, &c, 1);
	opt->arg_length += 1;
}

int			count_digit(uintmax_t nb, unsigned int base)
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

char		*u_itoa(uintmax_t nb, char *base_char, int base)
{
	char	*str;
	int		len;

	str = NULL;
	len = count_digit(nb, base);
	if (!(str = ft_strnew(len)))
		return (NULL);
	len--;
	if (!nb)
		str[len] = '0';
	while (nb)
	{
		str[len--] = base_char[nb % base];
		nb /= base;
	}
	return (str);
}
