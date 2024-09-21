/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:41:03 by franmart          #+#    #+#             */
/*   Updated: 2024/09/21 16:50:32 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    print_files_info(t_list *files, t_config *conf)
{
	t_file_info	*file;
	(void) conf;

	while (files)
	{
		file = files->content;
		ft_printf("%s\n", file->path);
		files = files->next;
	}
}