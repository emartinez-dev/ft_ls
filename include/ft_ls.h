/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:40:17 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 14:46:40 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define S_ISEXC(mode)  ((mode) & (S_IXUSR | S_IXGRP | S_IXOTH))

# include "libft.h"

# include <dirent.h>
# include <errno.h>
# include <linux/limits.h>
# include <grp.h>
# include <pwd.h>
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
void	recurse_files(t_list *file_info, t_config *conf);

/* file_info.c */
t_list	*get_file_info(t_list *paths, t_config *conf);
char	*get_file_name(char *path);
char	*join_paths(char *p1, char *p2);

/* output.c */
void    print_files_info(t_list *files, t_config *conf);
void    print_file_info(t_file_info *file, t_config *conf);
void	print_files_blocks(t_list *files);
void	print_long_output(t_file_info *file);
void	print_permissions(t_file_info *file);

/* parser.c */
t_list	*parse_args(char *arg, t_config *conf);

/* sort.c */
void		sort_paths_alphabetically(t_list *head);
void		sort_paths_by_date(t_list *head);
char		**msort_str(char **str_arr, size_t size);
t_file_info	**msort_date(t_file_info **file_arr, size_t size);

#endif