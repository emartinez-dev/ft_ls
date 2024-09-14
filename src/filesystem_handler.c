/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:38:12 by franmart          #+#    #+#             */
/*   Updated: 2024/09/14 18:48:00 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	handle_files(struct stat *sb, t_config *config, char *name)
{
	(void) sb;
	(void) config;
	ft_printf("\tfile: %s\n", name);
};

void	handle_links(struct stat *sb, t_config *config, char *name)
{
	(void) sb;
	(void) config;
	ft_printf("\tlink: %s\n", name);
};

void	handle_dirs(struct stat *sb, t_config *config, char *name)
{
	(void) sb;
	(void) config;
	ft_printf("\tdir: %s\n", name);
};

void	list_paths(t_list *paths, t_config *config)
{
	struct stat sb = {0};
	(void) config;

	while (paths)
	{
		if (stat(paths->content, &sb))
			ft_printf("ft_ls: cannot access '%s': %s\n", paths->content,
						strerror(errno));
		else
		{
			if (S_ISREG(sb.st_mode))
				handle_files(&sb, config, paths->content);
			else if (S_ISLNK(sb.st_mode))
				handle_links(&sb, config, paths->content);
			else if (S_ISDIR(sb.st_mode))
				handle_dirs(&sb, config, paths->content);
		}
		paths = paths->next;
	}
}