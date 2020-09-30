#include "../header.h"
#include <fcntl.h>

void	ft_exit(char *str, char *str2)
{
	if (str && str2)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(str2, 2);
		exit(EXIT_FAILURE);
	}
	perror(NULL);
	exit(EXIT_FAILURE);
}

int         open_and_check_file(int argc, char **argv)
{
    int fd;

    if (argc > 2)
        ft_exit(NULL, NULL);
    if ((fd = open(argv[1], O_RDONLY)) < 0)
        ft_exit(NULL, NULL);
    return (fd);
}

t_list      *read_file_to_list(int fd)
{
    char        **line;
    t_list      *list_root;
    t_list      *list_line;
    t_list      *list_head;

    list_root = ft_lstnew("root\n", 5);
    list_head = list_root;
    while (get_next_line(fd, line))
    {
        if (!(list_line = (t_list*)malloc(sizeof(t_list))))
            ft_exit(NULL, NULL);
        list_line->content = *line;
        list_head = ft_lstaddtohead(list_head, list_line);
    }
    return (list_root);
}



void        read_map_from_list(t_list *list_root)
{
    while (list_root)
    {
        ft_putendl(list_root->content);
        list_root = list_root->next;
    }
}

t_list     *check_args(int argc, char **argv)
{
    int         fd;
    t_ref_obj   *objs;
    t_list      *list_root;
    
    fd = open_and_check_file(argc, argv);
    list_root = read_file_to_list(fd);
    // read_map_from_list(list_root);
    return (list_root);
}