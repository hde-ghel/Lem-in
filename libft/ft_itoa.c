/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:54:31 by hde-ghel          #+#    #+#             */
/*   Updated: 2018/10/28 11:45:43 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_iotasign(int *n, int *sign)
{
	if (*n < 0)
	{
		*sign = 1;
		*n = *n * -1;
	}
}

static int	ft_itoalen(int j)
{
	int		len;

	len = 0;
	while (j != 0)
	{
		j = j / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*nbr;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 0;
	sign = 0;
	ft_iotasign(&n, &sign);
	len = ft_itoalen(n);
	len = len + sign;
	if (n == 0)
		len = len + 1;
	if (!(nbr = ft_strnew(len)))
		return (NULL);
	while (len--)
	{
		nbr[len] = n % 10 + '0';
		n = n / 10;
	}
	if (sign == 1)
		nbr[0] = '-';
	return (nbr);
}
