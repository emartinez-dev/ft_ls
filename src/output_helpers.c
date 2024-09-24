/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:38:16 by franmart          #+#    #+#             */
/*   Updated: 2024/09/24 13:17:09 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "colors.h"

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
	ft_putchar(' ');
}

void	print_date(t_file_info *file)
{
	time_t	current_time;
	char	*file_year;
	char	*file_date;
	char	*current_year;
	char	*current_date;
	char	*date;

	time(&current_time);
	current_date = ctime(&current_time);
	current_year = ft_substr(current_date, 20, 4);

	file_date = ctime(&file->stat_info.st_mtime);
	file_year = ft_substr(file_date, 20, 4);

	// With printf print limit this mallocs wouldn't be neccesary
	date = ft_substr(file_date, 4, 6);
	ft_printf("%s ", date);
	free(date);
	if (!ft_strncmp(file_year, current_year, ft_strlen(file_year)))
	{
		date = ft_substr(file_date, 11, 5);
		ft_printf("%s ", date);
		free(date);
	}
	else
		ft_printf(" %s ", file_year);
	free(current_year);
	free(file_year);
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

void    print_link_long(t_file_info *file, char *filename)
{
	char	    *lnk_file;

	lnk_file = ft_calloc(256, sizeof(char));
	readlink(file->path, lnk_file, 256);
	ft_printf("%s%s%s -> %s\n", LNK_COLOR, filename, RESET, lnk_file);
	free(lnk_file);
}

int     number_width(unsigned long long n)
{
	int width = 0;

	if (n == 0)
		return (1);
	while (n != 0)
	{
		width++;
		n = n / 10;
	}
	return (width);
}

void    print_number_with_padding(unsigned long long n, int width)
{
	int	n_width = number_width(n);

	while (n_width < width)
	{
		ft_putchar(' ');
		n_width++;
	}
	ft_printf("%l ", n);
}

void	get_widths(t_list *files, t_config *conf)
{
	t_file_info	*file;
	nlink_t		max_nlink = 0;
	off_t		max_size = 0;

	while (files)
	{
		file = files->content;
		if (file->stat_info.st_size > max_size)
			max_size = file->stat_info.st_size;
		if (file->stat_info.st_nlink > max_nlink)
			max_nlink = file->stat_info.st_nlink;
		files = files->next;
	}
	conf->size_width = number_width(max_size);
	conf->links_width = number_width(max_nlink);
}