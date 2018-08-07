/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 10:15:29 by itiievsk          #+#    #+#             */
/*   Updated: 2018/08/06 10:15:31 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./libft/libft.h"
# define FLAGS "Ralrt"

typedef struct		s_flags
{
	int				longform;
	int				dotfiles;
	int				revsort;
	int				recursive;
	int				timesort;
}					t_flags;

typedef struct		s_ls
{
	int				files;
	int				flags;
	int				*argc;
	char			**objs;
}					t_ls;

void				check_args(int argc, char **argv, t_flags *flags, t_ls *ls);
void				init_struct(t_flags *flags, t_ls *ls, int size);
void				wrong_arg(t_flags *flags, t_ls *ls, char ch);
#endif
