/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 15:06:47 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/14 15:06:49 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		define_time(t_flags *flags, t_file *file)
{
	if (flags->time_type == 'c')
	{
		file->ftime = file->stat.st_ctime;
		file->nsec = file->stat.st_ctimespec.tv_nsec;
	}
	else if (flags->time_type == 'u')
	{
		file->ftime = file->stat.st_atime;
		file->nsec = file->stat.st_atimespec.tv_nsec;
	}
	else if (flags->time_type == 'U')
	{
		file->ftime = file->stat.st_birthtime;
		file->nsec = file->stat.st_birthtimespec.tv_nsec;
	}
	else
	{
		file->ftime = file->stat.st_mtime;
		file->nsec = file->stat.st_mtimespec.tv_nsec;
	}
}
