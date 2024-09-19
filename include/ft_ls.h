/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:40:17 by franmart          #+#    #+#             */
/*   Updated: 2024/09/19 23:01:44 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

# include <dirent.h>
# include <errno.h>
# include <linux/limits.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>

/* I am an outer core student, could I pls just use stdbool? */
typedef enum { false, true } bool;
# define true  1
# define false 0

typedef struct s_args
{
	bool l_long;
	bool R_recursive;
	bool a_hidden;
	bool r_reverse;
	bool t_date_sort;
}   t_config;

typedef struct s_file_info
{
	char		*path;
	struct stat	stat_info;
}	t_file_info;

/* filesystem_handler.c */
void	list_initial_paths(t_list *paths, t_config *config);
void	list_dir(t_config *config, char *path);

/* file_info.c */
t_list	*get_file_info(t_list *paths, bool long_output, bool sort_by_date);

/* parser.c */
t_list	*parse_args(char *arg, t_config *conf);

/* sort.c */
void		sort_str_list_inplace(t_list *head);
void		sort_date_list_inplace(t_list *head);
char		**msort_str(char **str_arr, size_t size);
t_file_info	**msort_date(t_file_info **file_arr, size_t size);

/* utils.c */
void	print_config(t_config *conf);
void    print_paths(t_list *paths);
void    print_files(t_file_info *info);
void	do_nothing(void *ptr);
char	*join_paths(char *p1, char *p2);

#endif