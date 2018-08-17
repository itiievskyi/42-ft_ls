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

void		frontbacksplit(t_file *source, t_file **frontref, t_file **backref)
{
	t_file *fast;
	t_file *slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}

void		sort_size_list(t_file **file)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *file;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontbacksplit(head, &a, &b);
	sort_size_list(&a);
	sort_size_list(&b);
	*file = sorted_size_merge(a, b);
}

void		sort_time_list(t_file **file)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *file;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontbacksplit(head, &a, &b);
	sort_time_list(&a);
	sort_time_list(&b);
	*file = sorted_time_merge(a, b);
}

void		sort_alpha_list(t_file **file)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *file;
	if ((head == NULL) || (head->next == NULL))
		return ;
	frontbacksplit(head, &a, &b);
	sort_alpha_list(&a);
	sort_alpha_list(&b);
	*file = sorted_alpha_merge(a, b);
}

void		sort_list(t_file **file, t_flags *flags)
{
	t_file	*head;
	t_file	*a;
	t_file	*b;

	head = *file;
	if (flags->nosort == 0)
	{
		sort_alpha_list(file);
		if (flags->timesort == 1 && flags->sizesort == 0)
			sort_time_list(file);
		if (flags->sizesort == 1)
			sort_size_list(file);
		if (flags->revsort == 1)
			rev_sort(file);
	}
	else
	{
		if ((head == NULL) || (head->next == NULL))
			return ;
		frontbacksplit(head, &a, &b);
		sort_list(&a, flags);
		sort_list(&b, flags);
		*file = sorted_system_merge(a, b);
	}
}
