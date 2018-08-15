/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 13:39:10 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/14 13:39:11 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_d_list(char *arg, t_flags *flags, t_ls *ls, char *buf)
{
	struct stat	stat;
	DIR			*dir;
	char		*error;

	error = NULL;
	arg ? readlink(arg, buf, 1024) : 0;
	dir = opendir(arg);
	dir == NULL ? error = ft_strdup(strerror(errno)) : 0;
	if (ft_strlen(buf) > 0 && flags->longform == 1)
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (ft_strlen(buf) > 0 && dir == NULL &&
	ft_strequ(error, "No such file or directory") &&
	!lstat(arg, &stat))
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	else if (arg && dir == NULL &&
	ft_strequ(error, "No such file or directory"))
		t_file_pushback(&(ls->err), arg, error, flags);
	else if (arg)
		t_file_pushback(&(ls->files), arg, ls->path, flags);
	error == NULL ? 0 : free(error);
	dir == NULL ? 0 : closedir(dir);
}
