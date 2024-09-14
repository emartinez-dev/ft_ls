#include "ft_ls.h"

int main(int argc, char **argv)
{
	(void) argc;
	t_config	conf = {0};
	t_list		*paths;
	t_list		*new_path;

	int i = 0;
	while (argv[++i])
	{
		new_path = parse_args(argv[i], &conf);
		/*
		This could be optimized as ft_lstadd_back always travels the list
		to add another node from head, will be fine for low arg count
		*/
		if (new_path)
			ft_lstadd_back(&paths, new_path);
	}
	ft_printf("Parsed configuration:\n");
	print_config(&conf);
	ft_printf("\nParsed paths:\n");
	print_paths(paths);
	return (0);
}