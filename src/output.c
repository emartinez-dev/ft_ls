/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:41:03 by franmart          #+#    #+#             */
/*   Updated: 2024/09/21 17:39:49 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "colors.h"

void    print_files_info(t_list *files, t_config *conf)
{
	t_file_info	*file;
	(void) conf;

	while (files)
	{
		file = files->content;
		print_file_info(file, conf);
		files = files->next;
	}
}

void	print_file_info(t_file_info	*file, t_config	*conf)
{
	char		*filename;

	filename = get_file_name(file->path);
	if (conf->l_long)
	{
		;
	}
	if (S_ISDIR(file->stat_info.st_mode))
		ft_printf("%s%s%s\n", DIR_COLOR, filename, RESET);
	else if (S_ISLNK(file->stat_info.st_mode))
		ft_printf("%s%s%s\n", LNK_COLOR, filename, RESET);
	else if (S_ISEXC(file->stat_info.st_mode))
		ft_printf("%s%s%s\n", EXC_COLOR, filename, RESET);
	else
		ft_printf("%s\n", filename);
}