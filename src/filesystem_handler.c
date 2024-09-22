/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:38:12 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 20:13:04 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list_dir(t_config *conf, char *path)
{
	t_list			*paths = NULL;
	t_list			*files_info;
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", path, strerror(errno));
		return ;
	}
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.' || conf->a_hidden)
			ft_lstadd_front(&paths, ft_lstnew(join_paths(path, entry->d_name)));
	paths = ft_lstreverse(paths);
	closedir(dir);
	files_info = get_file_info(paths, conf);
	if (conf->R_recursive)
	{
		ft_printf("%s:\n", path);
		recurse_files(files_info, conf);
	}
	else
		print_files_info(files_info, conf);
	ft_lstclear(&paths, free);
	ft_lstclear(&files_info, free);
};

void	list_initial_paths(t_list *paths, t_config *config)
{
	struct stat sb = {0};
	t_file_info	file = {0};
	size_t		initial_paths = ft_lstsize(paths);

	if (config->r_reverse)
		paths = ft_lstreverse(paths);
	while (paths)
	{
		if (lstat(paths->content, &sb))
			ft_printf("ft_ls: cannot access '%s': %s\n", paths->content,
					  strerror(errno));
		else
		{
			if (S_ISDIR(sb.st_mode))
			{
				if (initial_paths > 1 && !config->R_recursive)
					ft_printf("%s:\n", paths->content);
				list_dir(config, paths->content);
				if (paths->next)
					ft_printf("\n");
			}
			else
			{
				file.path = paths->content;
				file.stat_info = sb;
				print_file_info(&file, config);
				ft_printf("\n");
			}
		}
		paths = paths->next;
	}
}

void	recurse_files(t_list *file_info, t_config *conf)
{
	t_file_info	*entry;
	char		*file;

	print_files_info(file_info, conf);
	while (file_info)
	{
		entry = file_info->content;
		file = get_file_name(entry->path);
		if (S_ISDIR(entry->stat_info.st_mode) && entry->stat_info.st_size != 0 &&
		 	ft_strncmp(file, "..", 3) && ft_strncmp(file, ".", 2))
			list_dir(conf, entry->path);
		file_info = file_info->next;
	}
}