/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strany.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:15:20 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/03 23:51:18 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** strany
** returns a pointer to the first matching character specifier(s).
*/

char	*strany(const char *string, char *specifiers)
{
	size_t	a;
	size_t	b;

	a = 0;
	while (string[a])
	{
		b = 0;
		while (specifiers[b])
		{
			if (string[a] == specifiers[b])
				return ((char *)(&string[a]));
			++b;
		}
		++a;
	}
	return (NULL);
}

/*
** stranyskip, strcanyskip
** returns a pointer to the first non-matching character specifier.
*/

char	*strany_skip(const char *string, char *specifiers)
{
	size_t	a;
	size_t	b;
	char	skip;

	a = 0;
	while (string[a])
	{
		b = 0;
		skip = FALSE;
		while (specifiers[b])
		{
			if (string[a] == specifiers[b])
			{
				skip = TRUE;
				break ;
			}
			++b;
		}
		if (skip == FALSE)
			return ((char *)(&string[a]));
		++a;
	}
	return (NULL);
}

char	*strchr_skip(const char *string, char specifier)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != specifier)
			return ((char *)(string + i));
		++i;
	}
	return (NULL);
}
