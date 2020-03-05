/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 15:27:24 by hde-ghel          #+#    #+#             */
/*   Updated: 2018/11/04 16:33:29 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	int		i;
	int		j;

	if (!s || !f)
		return (NULL);
	i = 0;
	j = ft_strlen((char *)s);
	if (!(dst = ft_strnew(j)))
		return (NULL);
	while (i != j)
	{
		dst[i] = f(s[i]);
		i++;
	}
	return (dst);
}
