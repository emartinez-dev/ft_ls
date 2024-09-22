/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:41:03 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 18:25:29 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "colors.h"

void    print_files_info(t_list *files, t_config *conf)
{
	t_file_info	*file;

	if (conf->l_long)
		print_files_blocks(files);
	get_widths(files, conf);
	while (files)
	{
		file = files->content;
		print_file_info(file, conf);
		files = files->next;
	}
	ft_printf("\n");
}

void	print_file_info(t_file_info	*file, t_config	*conf)
{
	char	*filename;
	char	*sep;

	filename = get_file_name(file->path);
	sep = SEP;
	if (conf->l_long)
	{
		print_long_output(file, conf);
		sep = LONG_SEP;
	}
	if (S_ISDIR(file->stat_info.st_mode))
		ft_printf("%s%s%s%s", DIR_COLOR, filename, RESET, sep);
	else if (S_ISLNK(file->stat_info.st_mode))
	{
		if (conf->l_long)
			print_link_long(file, filename);
		else
			ft_printf("%s%s%s%s", LNK_COLOR, filename, RESET, sep);

	}
	else if (S_ISEXC(file->stat_info.st_mode))
		ft_printf("%s%s%s%s", EXC_COLOR, filename, RESET, sep);
	else
		ft_printf("%s%s", filename, sep);
}

void	print_long_output(t_file_info *file, t_config *conf)
{
	struct passwd	*pw;
	struct group	*grp;
	struct stat		*sb;

	sb = &file->stat_info;
	pw = getpwuid(sb->st_uid);
	grp = getgrgid(sb->st_gid);
	print_permissions(file);
	print_number_with_padding(sb->st_nlink, conf->links_width);
	if (pw->pw_name)
		ft_printf("%s ", pw->pw_name);
	else
		ft_printf("%u ", pw->pw_gid);
	if (grp->gr_name)
		ft_printf("%s ", grp->gr_name);
	else
		ft_printf("%u ", grp->gr_gid);
	print_number_with_padding(sb->st_size, conf->size_width);
	print_date(file);
}
