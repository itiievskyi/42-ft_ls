/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_long_attr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 12:08:08 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/14 12:08:36 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_acl_last(t_file *file)
{
	ssize_t		xattr;
	acl_t		acl;

	acl = NULL;
	xattr = listxattr(file->full, NULL, 0, XATTR_NOFOLLOW);
	xattr = (xattr < 0 ? 0 : xattr);
	if (xattr > 0)
		file->chmod[9] = '@';
	else if ((acl = acl_get_link_np(file->full, ACL_TYPE_EXTENDED)))
		file->chmod[9] = '+';
	else
		file->chmod[9] = ' ';
	if (acl)
		free (acl);
}

void		define_chmod(t_file *file)
{
	mode_t 		val;

	val = (file->stat.st_mode & ~S_IFMT);
	file->chmod[0] = ((val & S_IRUSR) ? 'r' : '-');
	file->chmod[1] = ((val & S_IWUSR) ? 'w' : '-');
	file->chmod[2] = ((val & S_IXUSR) ? 'x' : '-');
	file->chmod[3] = ((val & S_IRGRP) ? 'r' : '-');
	file->chmod[4] = ((val & S_IWGRP) ? 'w' : '-');
	file->chmod[5] = ((val & S_IXGRP) ? 'x' : '-');
	file->chmod[6] = ((val & S_IROTH) ? 'r' : '-');
	file->chmod[7] = ((val & S_IWOTH) ? 'w' : '-');
	file->chmod[8] = ((val & S_IXOTH) ? 'x' : '-');
	((val & S_ISVTX) && (val & S_IXOTH)) ? file->chmod[8] = 't' : 0;
	((val & S_ISVTX) && !(val & S_IXOTH)) ? file->chmod[8] = 'T' : 0;
	((val & S_ISUID) && (val & S_IXUSR)) ? file->chmod[2] = 's' : 0;
	((val & S_ISUID) && !(val & S_IXUSR)) ? file->chmod[2] = 'S' : 0;
	((val & S_ISGID) && (val & S_IXGRP)) ? file->chmod[5] = 's' : 0;
	((val & S_ISGID) && !(val & S_IXGRP)) ? file->chmod[5] = 'S' : 0;
	get_acl_last(file);
}

char		define_type(t_file *file)
{
	if (S_ISDIR(file->stat.st_mode))
		return ('d');
	if (S_ISCHR(file->stat.st_mode))
		return ('c');
	if (S_ISBLK(file->stat.st_mode))
		return ('b');
	if (S_ISLNK(file->stat.st_mode))
	{
		file->target = (char*)malloc(sizeof(char) * file->stat.st_size + 1);
		readlink(file->full, file->target, file->stat.st_size + 1);
		file->target[file->stat.st_size] = '\0';
		return ('l');
	}
	if (S_ISSOCK(file->stat.st_mode))
		return ('s');
	if (S_ISFIFO(file->stat.st_mode))
		return ('p');
	return ('-');
}

void		get_owner(t_pstat *pstat, t_file *file)
{
	int				usr_len;
	int				grp_len;
	struct passwd	*passwd;
	struct group	*group;

	group = NULL;
	passwd = NULL;
	passwd = getpwuid(file->stat.st_uid);
	if (passwd)
		file->user = ft_strdup(passwd->pw_name);
	else
		file->user = ft_strdup(ft_itoa(file->stat.st_uid));
	usr_len = ft_strlen(file->user);
	usr_len > pstat->maxusr ? pstat->maxusr = usr_len : 0;
	group = getgrgid(file->stat.st_gid);
	if (group)
		file->group = ft_strdup(group->gr_name);
	else
		file->group = ft_strdup(ft_itoa(file->stat.st_gid));
	grp_len = ft_strlen(file->group);
	grp_len > pstat->maxgrp ? pstat->maxgrp = grp_len : 0;
}
