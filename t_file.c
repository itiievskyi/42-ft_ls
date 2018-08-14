/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 16:33:24 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 16:33:26 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		count_list_length(t_file *file)
{
	t_file		*temp;
	int			length;

	temp = file;
	length = 0;
	while (temp)
	{
		length++;
		temp = temp->next;
	}
	return (length);
}

t_file	*t_file_new(char *name, char *cat, t_flags *flags)
{
	t_file	*file;
	char	*temp;

	file = (t_file*)malloc(sizeof(t_file));
	file->name = ft_strdup(name);
	file->path = ft_strdup(cat);
	if ((cat && cat[0] != '\0'))
	{
		temp = ft_strjoin(cat, "/");
		file->full = ft_strjoin(temp, name);
		free(temp);
	}
	else if (cat)
		file->full = ft_strjoin("", name);
	file->next = NULL;
	file->prev = NULL;
	lstat(file->full, &file->stat);
	init_t_file(file);
	define_time(flags, file);
	return (file);
}

int		t_file_pushback(t_file **begin, char *name, char *cat, t_flags* flags)
{
	t_file *temp;

	temp = *begin;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = t_file_new(name, cat, flags);
		temp->next->prev = temp;
	}
	else if (name)
		*begin = t_file_new(name, cat, flags);
	else
		return (0);
	return (1);
}
