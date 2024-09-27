/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:32:58 by franmart          #+#    #+#             */
/*   Updated: 2024/09/27 20:27:38 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv)
{
	(void)		argc;
	t_config	conf = {0};
	t_list		*paths = NULL;
	t_list		*new_path;

	int i = 0;
	while (argv[++i])
	{
		new_path = parse_args(argv[i], &conf);
		if (new_path)
			ft_lstadd_front(&paths, new_path);
	}
	if (!paths)
		paths = ft_lstnew(ft_strdup("."));
	paths = list_initial_paths(paths, &conf);
	ft_printf_flush_buffer();
	ft_lstclear(&paths, free);
	ft_lstclear(&conf.users, free_user_info);
	ft_lstclear(&conf.groups, free_group_info);
	return (0);
}