/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:32:58 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 12:26:43 by franmart         ###   ########.fr       */
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
		if (new_path)
			ft_lstadd_front(&paths, new_path);
	}
	char	*cwd = ft_strdup(".");
	if (!paths)
		paths = ft_lstnew(cwd);
	list_initial_paths(paths, &conf);
	ft_lstclear(&paths, ft_do_nothing);
	free(cwd);
	return (0);
}