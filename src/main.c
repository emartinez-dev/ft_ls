#include "ft_ls.h"

int main(int argc, char **argv)
{
	(void) argc;
	t_config conf = {0};

	int i = 0;
	while (argv[++i])
		parse_args(argv[i], &conf);
	ft_printf("Parsed configuration:\n");
	print_config(&conf);
	return (0);
}
