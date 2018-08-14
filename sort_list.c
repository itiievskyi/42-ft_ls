/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:06:57 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/08 18:06:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		swap_t_file(t_file *one, t_file *two)
{
	ft_str_swap(&(one->name), &(two->name));
	ft_str_swap(&(one->path), &(two->path));
	ft_str_swap(&(one->full), &(two->full));
	ft_stat_swap(&(one->stat), &(two->stat));
	ft_time_swap(&(one->nsec), &(two->nsec));
	ft_time_swap(&(one->ftime), &(two->ftime));
}

void		rev_sort(t_file *file, int i, int j)
{
	t_file	*a;
	t_file	*b;
	int		len;

	len = count_list_length(file);
	while (++i < len / 2)
	{
		j = 0;
		a = file;
		b = file;
		while (j++ < i)
			a = a->next;
		j = 0;
		while (j++ < len - i - 1)
			b = b->next;
		swap_t_file(a, b);
	}
}

void		time_sort(t_file *file)
{
	t_file	*temp;

	temp = file;
	while (temp && temp->next)
	{
		if (temp->ftime < temp->next->ftime)
		{
			swap_t_file(temp, temp->next);
			temp = file;
		}
		else if ((temp->ftime == temp->next->ftime) &&
		(temp->nsec < temp->next->nsec))
		{
			swap_t_file(temp, temp->next);
			temp = file;
		}
		else
			temp = temp->next;
	}
}

void		alpha_sort(t_file *file)
{
	t_file	*temp;

	temp = file;
	while (temp && temp->next)
	{
		if (ft_strcmp(temp->name, temp->next->name) > 0)
		{
			swap_t_file(temp, temp->next);
			temp = file;
		}
		else
			temp = temp->next;
	}
}

void		sort_list(t_file *file, t_flags *flags)
{
	alpha_sort(file);
	if (flags->timesort == 1 && flags->sizesort == 0)
		time_sort(file);
	if (flags->sizesort == 1)
		size_sort(file);
	if (flags->revsort == 1)
		rev_sort(file, -1, 0);
}
