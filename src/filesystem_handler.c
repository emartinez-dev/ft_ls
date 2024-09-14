/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:38:12 by franmart          #+#    #+#             */
/*   Updated: 2024/09/14 21:26:41 by franmart         ###   ########.fr       */
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

void	list_dir(t_config *config, char *path)
{
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)))
	{
		char *entry_path = join_paths(path, entry->d_name);

		if (entry->d_name[0] == '.' && !config->a_hidden) {}
		else if (entry->d_type == DT_DIR)
		{
			if (config->R_recursive && ft_strncmp(entry->d_name, "..", 3)
									&& ft_strncmp(entry->d_name, ".", 2))
				list_dir(config, entry_path);
			ft_printf("%s\n", entry_path);
		}
		else if (entry->d_type == DT_REG)
			ft_printf("%s\n", entry_path);
		else if (entry->d_type == DT_LNK)
			ft_printf("%s\n", entry_path); // dont cause loops while recursing links
		else if (entry->d_type == DT_UNKNOWN)
			ft_printf("ft_ls: cannot access '%s': %s\n", entry_path, strerror(errno));
		free(entry_path);
	}
	closedir(dir);
};

void	list_paths(t_list *paths, t_config *config)
{
	struct stat sb = {0};

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
				list_dir(config, paths->content);
		}
		paths = paths->next;
	}
}