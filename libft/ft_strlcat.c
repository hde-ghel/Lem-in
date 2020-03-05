/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:34:51 by hde-ghel          #+#    #+#             */
/*   Updated: 2018/10/17 17:40:55 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t s;
	size_t j;
	size_t i;

	s = ft_strlen(src);
	j = ft_strlen(dst);
	if (size <= j)
		return (s + size);
	size = size - j - 1;
	i = 0;
	while (src[i] != '\0' && size > 0)
	{
		dst[j + i] = src[i];
		i++;
		size--;
	}
	dst[j + i] = '\0';
	return (s + j);
}
