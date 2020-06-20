/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:04:47 by hde-ghel          #+#    #+#             */
/*   Updated: 2019/02/19 16:33:02 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static	int		ft_check_rest(const int fd, char **rest, char **line)
{
	char	*p;
	char	*tmp;
	char	*ptr;

	ptr = *line;
	if ((p = ft_strchr(rest[fd], '\n')) == NULL)
	{
		if (!(*line = ft_strdup(rest[fd])))
			return (-1);
		ft_strdel(&rest[fd]);
	}
	else
	{
		if (!(*line = ft_strsub(rest[fd], 0, (p - rest[fd]))))
			return (-1);
		tmp = ft_strsub(rest[fd], (p - rest[fd]) + 1, ft_strlen(rest[fd]));
		if (!tmp)
			return (-1);
		ft_strdel(&rest[fd]);
		rest[fd] = tmp;
		ft_strdel(&ptr);
		return (1);
	}
	ft_strdel(&ptr);
	return (0);
}

static	int		ft_read_next_buff(int fd, char *buff, char **line, char **rest)
{
	int		i;
	char	*p;

	while ((i = read(fd, buff, BUFF_SIZE_GNL)) > 0)
	{
		buff[i] = '\0';
		if ((p = ft_strchr(buff, '\n')) == NULL)
		{
			if (!(*line = ft_strjoin_free(*line, buff, 1)))
				return (-1);
		}
		else
		{
			if (!(*line = ft_strjoin_free(*line, ft_strsub(buff, 0,
				(p - buff)), 3)))
				return (-1);
			if (!(rest[fd] = ft_strsub(buff, (p - buff) + 1, ft_strlen(buff))))
				return (-1);
			return (1);
		}
	}
	if (i == -1)
		return (-1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE_GNL + 1];
	static	char	*rest[OPEN_MAX];
	int				x;

	x = 0;
	if (fd < 0 || read(fd, buff, 0) == -1 || fd > OPEN_MAX
			|| !(*line = ft_strnew(0)))
		return (-1);
	if (rest[fd])
	{
		if ((x = (ft_check_rest(fd, rest, line))) != 0)
			return (x);
	}
	if ((x = (ft_read_next_buff(fd, buff, line, rest))) != 0)
		return (x);
	if (line[0][0] == '\0')
	{
		ft_strdel(line);
		return (0);
	}
	return (1);
}
