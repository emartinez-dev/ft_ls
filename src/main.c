/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:32:58 by franmart          #+#    #+#             */
/*   Updated: 2024/09/15 14:27:52 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	(void)		argc;
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
			ft_lstadd_front(&paths, new_path);
	}

	// Parsed all arguments, if paths is null (no file or folder specified), we should list CWD
	char	*cwd = ft_strdup(".");
	if (!paths)
		paths = ft_lstnew(cwd);

	/*
	ft_printf("Parsed configuration:\n");
	print_config(&conf);
	ft_printf("\nParsed paths:\n");
	print_paths(paths);
	*/

	list_initial_paths(paths, &conf);
	/* Free everything */
	ft_lstclear(&paths, do_nothing);
	free(cwd);
	return (0);
}