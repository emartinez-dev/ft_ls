/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:38:12 by franmart          #+#    #+#             */
/*   Updated: 2024/09/19 23:15:39 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void fileinfo_wrapper(void *file)
{
	print_files((t_file_info *) file);
}

void	list_dir(t_config *config, char *path)
{
	t_list			*paths = NULL;
	t_list			*file_info = NULL;
	t_list			*new_path;
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.' || config->a_hidden)
		{
			char *entry_path = join_paths(path, entry->d_name);
			new_path = ft_lstnew(entry_path);
			ft_lstadd_back(&paths, new_path);
		}
	}
	closedir(dir);
		sort_str_list_inplace(paths);
	file_info = get_file_info(paths, config->l_long, config->t_date_sort); // TODO: no printing right know when no l or t flags
	if (config->r_reverse)
		file_info = ft_lstreverse(file_info); // FUCK, THIS LEAKS
	ft_lstiter(file_info, fileinfo_wrapper);
	// 3. After printing, if any entry is a dir and recursive is on, list_dir on that folder
	// 4. Clear the allocated joint paths
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