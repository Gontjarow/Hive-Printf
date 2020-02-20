/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strany.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:15:20 by ngontjar          #+#    #+#             */
/*   Updated: 2020/02/20 20:22:50 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*strany(const char *string, const char *specifiers)
{
	size_t a;
	size_t b;

	a = 0;
	b = 0;
	while (string[a])
	{
		while (specifiers[b])
		{
			if (string[a] == specifiers[b])
				return (char *)(&string[a]);
			++b;
		}
		++a;
	}
	return (NULL);
}

char	*strcany(const char *string, const char specifier)
{
	size_t i;

	i = 0;
	while (string[i])
	{
		if(string[i] == specifier)
			return (char *)(string + i);
		++i;
	}
	return (NULL);
}
