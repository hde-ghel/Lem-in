/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:05:15 by hde-ghel          #+#    #+#             */
/*   Updated: 2018/10/28 11:38:34 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	size_t			len;
	char			*dest;

	if (!(s))
		return (NULL);
	len = ft_strlen(s);
	if (len == 0)
		return ((char *)s);
	start = 0;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	if (s[start] == '\0')
	{
		if (!(dest = ft_strdup("")))
			return (NULL);
		return (dest);
	}
	while (s[len - 1] == ' ' || s[len - 1] == '\t' || s[len - 1] == '\n')
		len--;
	len = len - start;
	if (!(dest = ft_strsub(s, start, len)))
		return (NULL);
	return (dest);
}
