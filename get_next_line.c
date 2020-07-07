/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sookim <sookim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:31:47 by sookim            #+#    #+#             */
/*   Updated: 2020/07/07 17:32:49 by sookim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					ft_new_line_check(char *temp_buf)
{
	int				i;

	i = 0;
	while (temp_buf[i])
	{
		if (temp_buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int					ft_line_split(char **temp_buf, char **line, int new_line_idx)
{
	char			*new_temp_buf;
	int				len;

	(*temp_buf)[new_line_idx] = '\0';
	*line = ft_strdup(*temp_buf);
	len = ft_strlen(*temp_buf + new_line_idx + 1);
	if (len == 0)
	{
		free(*temp_buf);
		*temp_buf = 0;
		return (1);
	}
	new_temp_buf = ft_strdup(*temp_buf + new_line_idx + 1);
	free(*temp_buf);
	*temp_buf = new_temp_buf;
	return (1);
}

int					return_all(char **temp_buf, char **line, int read_size)
{
	int				new_line_idx;

	if (read_size < 0)
		return (-1);
	if (*temp_buf && (new_line_idx = ft_new_line_check(*temp_buf)) >= 0)
		return (ft_line_split(temp_buf, line, new_line_idx));
	else if (*temp_buf)
	{
		*line = *temp_buf;
		*temp_buf = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*temp_buf[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	int				new_line_idx;

	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE < 1))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		temp_buf[fd] = ft_strjoin(temp_buf[fd], buf);
		if ((new_line_idx = ft_new_line_check(temp_buf[fd])) >= 0)
			return (ft_line_split(&temp_buf[fd], line, new_line_idx));
	}
	return (return_all(&temp_buf[fd], line, read_size));
}