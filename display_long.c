/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 11:11:18 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/13 11:11:20 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		define_chmod(t_file *file)
{
	mode_t 		val;
	ssize_t		xattr;
	acl_t		acl;

	acl = NULL;
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

void		parse_list(t_pstat *pstat, t_file *file)
{
	t_file			*temp;
	int				lnk_len;
	int				size_len;

	temp = file;
	while (temp)
	{
		pstat->total += (temp->stat).st_blocks;
		lnk_len = ft_intlen(temp->stat.st_nlink);
		size_len = ft_intlen(temp->stat.st_size);
		lnk_len > pstat->maxlnk ? pstat->maxlnk = lnk_len : 0;
		size_len > pstat->maxsize ? pstat->maxsize = size_len : 0;
		temp->type = define_type(temp);
		define_chmod(temp);
		get_owner(pstat, temp);
		temp = temp->next;
	}
}

void		display_long(t_ls *ls, t_file *file)
{
	t_file			*temp;
	t_pstat			*pstat;

	temp = file;
	pstat = (t_pstat*)malloc(sizeof(t_pstat));
	init_pstat(pstat);
	parse_list(pstat, file);
	(file == ls->files) ? 0 : ft_printf("total %d\n", pstat->total);
	while (temp && ls)
	{
		ft_printf("%c%s %*d %-*s %-*s  %*d ",
		temp->type, temp->chmod, pstat->maxlnk, temp->stat.st_nlink,
		pstat->maxusr, temp->user, pstat->maxgrp, temp->group,
		pstat->maxsize, temp->stat.st_size);
		(time(NULL) - temp->stat.st_mtime < 15780000 &&
		temp->stat.st_mtime - time(NULL) < 15780000) ?
		ft_printf("%.12s", ctime(&temp->stat.st_mtime) + 4) :
		ft_printf("%.7s %.4s", ctime(&temp->stat.st_mtime) + 4,
		ctime(&temp->stat.st_mtime) + 20);
		ft_printf(" %s", temp->name);
		if (temp->type == 'l' && temp->target)
			ft_printf(" -> %s", temp->target);
		write(1, "\n", 1);
		temp = temp->next;
	}
}
