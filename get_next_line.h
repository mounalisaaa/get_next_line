# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

typedef struct s_list
{
	char *content;
	struct s_list *next;
} t_list;

char	*get_next_line(int fd);


#endif
