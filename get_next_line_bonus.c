/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyaaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:07:30 by melyaaco          #+#    #+#             */
/*   Updated: 2023/11/17 14:33:46 by melyaaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_addback(t_list **lst, char *buff)
{
	t_list	*node;
	t_list	*curr;

	curr = *lst;
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = buff;
	node->next = NULL;
	if (!(*lst))
	{
		*lst = node;
		return (1);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return (1);
}

char	*helper(t_list **lst, int fd)
{
	char			*buff;
	ssize_t			bytesread;

	while (1)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread <= 0)
		{
			free(buff);
			return (ft_line(lst));
		}
		buff[bytesread] = '\0';
		if (!(ft_addback(lst, buff)))
			return (NULL);
		if (ft_strchr(buff, '\n'))
			return (ft_line(lst));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_arr[1024];

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 0xffffffff
		|| (read(fd, NULL, 0)) < 0)
		return (NULL);
	if (fd_arr[fd] && ft_strchr(fd_arr[fd]->content, '\n'))
		return (ft_line(&fd_arr[fd]));
	return (helper(&fd_arr[fd], fd));
}
