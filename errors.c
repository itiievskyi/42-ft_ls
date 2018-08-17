/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 17:45:42 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/09 17:45:43 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_errors(t_ls *ls)
{
	t_file	*temp;

	sort_alpha_list(&ls->err);
	temp = ls->err;
	if (temp)
	{
		while (temp)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(temp->name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(temp->path, 2);
			ft_putstr_fd("\n", 2);
			temp = temp->next;
		}
	}
}

void		print_cat_error(char *cat, char *error)
{
	char	**arr;
	int		a;

	a = 0;
	arr = ft_strsplit(cat, '/');
	while (arr[a + 1])
		a++;
	ft_putstr_fd("ft_ls: ", 2);
	if (cat)
		ft_putstr_fd(arr[a], 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	ft_clean_str_array(arr);
}
