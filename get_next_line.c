#include "get_next_line.h"

size_t ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*ans;
	size_t	i;

	ans = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!ans)
		return (0);
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int ft_addback(t_list **lst, char *buff)
{
	t_list	*node;
	t_list *curr;

	curr = *lst;
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = buff;
	node->next = NULL;
	if (!curr)
	{
		*lst = node;
		return (1);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = node;
	return(1);
}

int line_size(t_list *lst)
{
	int i;
	int ans;

	ans = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] && lst->content[i] != '\n')
		{
			i++;
			ans++;
		}
		if (lst->content[i] == '\n')
			ans++;
		lst = lst->next;
	}
	return (ans);
}

void ft_set_new(t_list **lst)
{
	char *new;
	t_list *node;

	if(!(ft_strchr((*lst)->content, '\n')))
	{
		*lst = NULL;
		return ;
	}
	new = ft_strdup(ft_strchr((*lst)->content, '\n') + 1);
	node = malloc(sizeof(t_list));
	node->next = NULL;
	node->content = new;
	*lst = node;
}

void ft_clear(t_list **lst)
{
	t_list *curr;
	t_list *next;

	curr = *lst;
	if (!(*lst))
		return ;
	while (curr->next)
	{
		next = curr->next;
		free(curr->content);
		free(curr);
		curr = next;
	}
	ft_set_new(lst);
	free(curr->content);
	free(curr);
}

char *ft_line(t_list **lst)
{
	t_list *curr;
	char *line;
	int i;
	int j;

	j = 0;
	curr = *lst;
	line = malloc(sizeof(char) * (line_size(curr) + 1));
	if (!line)
		return (NULL);
	while (curr)
	{
		i = 0;
		while(curr->content[i] && curr->content[i] != '\n')
			line[j++] = curr->content[i++];
		if (curr->content[i] == '\n')
			line[j++] = '\n';
		curr = curr->next;
	}
	line[j] = '\0';
	ft_clear(lst);
	return (line);
}

char	*get_next_line(int fd)
{
	char *buff;
	ssize_t bytesread;
	static t_list	*lst;

	while (1)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread == 0)
		{
			free(buff);
			return (ft_line(&lst));
		}
		buff[bytesread] = '\0';
		if (!(ft_addback(&lst, buff)))
			return (NULL);
		if (ft_strchr(buff, '\n'))
			return (ft_line(&lst));
	}	  
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>
int main (void)
{	
	int fd = open("text", 'r');
	char *s;
	s = get_next_line(fd);
	printf("%s", s);
	/*while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break;
		printf("%s", s);
		free(s);
	}*/
	return (0);
}
