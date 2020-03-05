/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:12:12 by hde-ghel          #+#    #+#             */
/*   Updated: 2019/10/12 17:35:28 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;
	unsigned int	j;

	if (!s || !f)
		return (NULL);
	i = 0;
	j = (unsigned int)ft_strlen((char *)s);
	if (!(dst = ft_strnew(j)))
		return (NULL);
	while (i != j)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	return (dst);
}
