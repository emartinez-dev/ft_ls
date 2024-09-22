/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:41:03 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 13:42:49 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "colors.h"

void    print_files_info(t_list *files, t_config *conf)
{
	t_file_info	*file;

	if (conf->l_long)
		print_files_blocks(files);
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
		print_long_output(file);
		sep = LONG_SEP;
	}
	if (S_ISDIR(file->stat_info.st_mode))
		ft_printf("%s%s%s%s", DIR_COLOR, filename, RESET, sep);
	else if (S_ISLNK(file->stat_info.st_mode))
		ft_printf("%s%s%s%s", LNK_COLOR, filename, RESET, sep);
	else if (S_ISEXC(file->stat_info.st_mode))
		ft_printf("%s%s%s%s", EXC_COLOR, filename, RESET, sep);
	else
		ft_printf("%s%s", filename, sep);
}

/* The value of stat.st_blocks has a blocksize of 512 bytes, but ls outputs them as if the
	blocksize was 1024 bytes (which is 1KB and more readable) */
void	print_files_blocks(t_list *files)
{
	unsigned int	count = 0;
	t_file_info		*file;

	while (files)
	{
		file = files->content;
		count = count + file->stat_info.st_blocks;
		files = files->next;
	}
	ft_printf("total %u\n", count / 2);
}

void	print_long_output(t_file_info *file)
{
	struct passwd	*pw;
	struct group	*grp;
	struct stat		*sb;

	sb = &file->stat_info;
	pw = getpwuid(sb->st_uid);
	grp = getgrgid(sb->st_gid);
	print_permissions(file);
	ft_printf(" %u ", sb->st_nlink);
	if (pw->pw_name)
		ft_printf("%s ", pw->pw_name);
	else
		ft_printf("%u ", pw->pw_gid);
	if (grp->gr_name)
		ft_printf("%s ", grp->gr_name);
	else
		ft_printf("%u ", grp->gr_gid);
	ft_printf("%u ", sb->st_size);
}

void	print_permissions(t_file_info *file)
{
	struct	stat sb = file->stat_info;

	if (S_ISDIR(sb.st_mode))
		ft_putchar('d');
	else if (S_ISLNK(sb.st_mode))
		ft_putchar('l');
	else
		ft_putchar('-');
	ft_putchar((sb.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((sb.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((sb.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((sb.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((sb.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((sb.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((sb.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((sb.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((sb.st_mode & S_IXOTH) ? 'x' : '-');
}