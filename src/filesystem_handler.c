/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:38:12 by franmart          #+#    #+#             */
/*   Updated: 2024/09/21 13:12:24 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void fileinfo_wrapper(void *file)
{
	print_files((t_file_info *) file);
}

void	list_dir(t_config *conf, char *path)
{
	t_list			*paths = NULL;
	t_list			*file_info = NULL;
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.' || conf->a_hidden)
			ft_lstadd_back(&paths, ft_lstnew(join_paths(path, entry->d_name)));
	closedir(dir);
	file_info = get_file_info(paths, conf);
	ft_lstiter(file_info, fileinfo_wrapper);
	if (conf->R_recursive)
		recurse_files(file_info, conf);
	ft_lstclear(&paths, free);
	ft_lstclear(&file_info, free);
};

void	list_initial_paths(t_list *paths, t_config *config)
{
	struct stat sb = {0};

	if (config->r_reverse)
		paths = ft_lstreverse(paths);
	while (paths)
	{
		if (stat(paths->content, &sb))
			ft_printf("ft_ls: cannot access '%s': %s\n", paths->content,
						strerror(errno));
		else
		{
			if (S_ISDIR(sb.st_mode))
				list_dir(config, paths->content);
			else if (S_ISLNK(sb.st_mode)) {} // what should I do with links
			else
				ft_printf("%s\n", paths->content); // this will be display_info
		}
		paths = paths->next;
	}
}