/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 15:01:11 by hde-ghel          #+#    #+#             */
/*   Updated: 2019/10/11 19:10:13 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)src;
	s2 = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		s2[i] = s1[i];
		if (s1[i] == (unsigned char)c)
			return (s2 + i + 1);
		i++;
	}
	return (NULL);
}
