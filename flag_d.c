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

void	get_d_list(char *arg, t_flags *flags, t_ls *ls)
{
	char 		*buf;
	struct stat	stat;

	buf = (char*)malloc(sizeof(char) * 1024);
	buf[0] = '\0';
	if (arg)
		readlink(arg, buf, 1024);
	if (ft_strlen(buf) > 0 && flags->longform == 1)
		t_file_pushback(&(ls->files), arg, ls->path);
	else if (ft_strlen(buf) > 0 && (opendir(arg)) == NULL &&
	ft_strequ(strerror(errno), "No such file or directory") &&
	!lstat(arg, &stat))
		t_file_pushback(&(ls->files), arg, ls->path);
	else if (arg && (opendir(arg)) == NULL &&
	ft_strequ(strerror(errno), "No such file or directory"))
		t_file_pushback(&(ls->err), arg, strerror(errno));
	else if (arg)
		t_file_pushback(&(ls->files), arg, ls->path);
	free(buf);
}
